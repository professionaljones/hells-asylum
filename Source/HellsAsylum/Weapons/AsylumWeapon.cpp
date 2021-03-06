// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumWeapon.h"
#include "Character/Player/AsylumPlayerCharacter.h"

// Sets default values
AAsylumWeapon::AAsylumWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	RootComponent = WeaponMesh;
	FireArrow = CreateDefaultSubobject<UArrowComponent>("FireLocationArrow");
	FireArrow->SetupAttachment(WeaponMesh, ProjectileSocket);
	WeaponAudioComponent = CreateDefaultSubobject<UAudioComponent>("WeaponAudioComponent");
	WeaponModsComponent = CreateDefaultSubobject<UWeaponModComponent>("WeaponModsComponent");

	ObjectsToTarget.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectsToTarget.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectsToTarget.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));

	WeaponLevelMap.Add(1, "1");
	WeaponLevelMap.Add(2, "2");
	WeaponLevelMap.Add(3, "3");
	WeaponLevelMap.Add(4, "4");
	WeaponLevelMap.Add(5, "5");

	if (WeaponStatsData.FireRate > 0)
	{
		bIsAutomatic = true;
	}
}

// Called when the game starts or when spawned
void AAsylumWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (bIsChargeWeapon)
	{
		ChargeDamageModifer = WeaponStatsData.DamageModifierAmount;
	}
	CheckAmmo();

	WeaponABP = WeaponMesh->GetAnimInstance();
}

void AAsylumWeapon::AttachToOwner()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetMesh();
		if (PawnMesh)
		{
			WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponAttachPoint);
			if (IsHidden())
			{
				this->SetActorHiddenInGame(false);
			}
			else
			{
				this->SetActorHiddenInGame(true);
			}
		}
	}
}

void AAsylumWeapon::SetWeaponOwner(AAsylumCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
		SetOwner(NewOwner);
	}
}

// Called every frame
void AAsylumWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsylumWeapon::ActivateWeaponModInSlot(EWeaponOffenseModType ModSelected)
{
	if (WeaponModsComponent->bIsSlotOneEnabled && !WeaponModsComponent->bIsModOneActive)
	{
		WeaponModsComponent->bIsModOneActive = true;
		if (ModSelected == WOM_FireAmmo)
		{
			WeaponStatsData.C_WeaponDamageType = C_FireDamageType;
			WeaponStatsData.DamageModifierAmount = WeaponStatsData.DamageModifierAmount + O_FireDamageType->fDamageModAmount;
		}
		if (ModSelected == WOM_IceAmmo)
		{
			WeaponStatsData.C_WeaponDamageType = C_IceDamageType;
			WeaponStatsData.DamageModifierAmount = WeaponStatsData.DamageModifierAmount + O_IceDamageType->fDamageModAmount;
		}
	}

}

void AAsylumWeapon::DeactivateWeaponModInSlot(EWeaponOffenseModType ModSelected)
{
	if (WeaponModsComponent->bIsSlotOneEnabled && WeaponModsComponent->bIsModOneActive)
	{
		WeaponModsComponent->bIsModOneActive = false;
		if (ModSelected == WOM_FireAmmo || ModSelected == WOM_IceAmmo)
		{
			WeaponStatsData.C_WeaponDamageType = C_OriginalDamageType;
			WeaponStatsData.DamageModifierAmount = WeaponStatsData.OriginalDamageModifier;
		}
	}

}

void AAsylumWeapon::CheckAmmo()
{
	if (!bEnableInfiniteAmmo)
	{
		if (WeaponStatsData.CurrentMagazineAmmo != 0 || WeaponStatsData.CurrentWeaponClips != 0)
		{
			bCanWeaponFire = true;
		}
		if (WeaponStatsData.CurrentMagazineAmmo <= 0 && bCanWeaponFire)
		{
			bCanWeaponFire = false;
			WeaponStatsData.CurrentMagazineAmmo = 0;
			this->Execute_OnEmptyWeaponFire(this);
		}
		else
		{
			bCanWeaponFire = true;
		}
		if (WeaponStatsData.CurrentMagazineAmmo < WeaponStatsData.MaxMagazineAmmo)
		{
			bCanReload = true;

		}
		else
		{
			bCanReload = false;
		}


		if (WeaponStatsData.CurrentWeaponClips <= 0)
		{
			bCanReload = false;
			bIsWeaponEmpty = true;
		}
	}
}

void AAsylumWeapon::StartFire()
{
	if (bCanWeaponFire && !bIsReloading)
	{
		if (bIsChargeWeapon)
		{
			StartCharge();
			if (bIsAutomatic && WeaponStatsData.WeaponAmmoType == AT_Energy)
			{
				StartCharge();
				GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AAsylumWeapon::Fire, WeaponStatsData.FireRate, true);
			}
		}
		if (bIsAutomatic)
		{
			Fire();
			GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AAsylumWeapon::Fire, WeaponStatsData.FireRate, true);
		}
		if (!bIsAutomatic && !bIsChargeWeapon)
		{
			Fire();
		}
	}
	if (!bCanWeaponFire)
	{
		WeaponDryFire();
		this->Execute_OnEmptyWeaponFire(this);
	}
}


void AAsylumWeapon::WeaponDryFire()
{
	if (WeaponDryFireSound != NULL)
	{
		WeaponAudioComponent->SetSound(WeaponDryFireSound);
		WeaponAudioComponent->Play();
	}

	if (WeaponStatsData.CurrentMagazineAmmo < 0)
	{
		WeaponStatsData.CurrentMagazineAmmo = 0;
	}
}

void AAsylumWeapon::Fire()
{
	//Collision parameters
	FCollisionQueryParams CollisionParameters;

	this->Execute_OnFire(this);

	//If this weapon is not reloading and has ammo in mag
	if (!bIsReloading && bCanWeaponFire)
	{

		//Consume ammo
		if (!bEnableInfiniteAmmo)
		{
			WeaponStatsData.CurrentMagazineAmmo = WeaponStatsData.CurrentMagazineAmmo - WeaponStatsData.AmmoConsumptionAmount;
		}



		//Create temp variable for Actor we hit
		AActor* HitActor = SingleHit.GetActor();

		//Length of the ray in Unreal units
		float WeaponRange = WeaponStatsData.WeaponDistanceRange;

		//Play Fire SFX
		if (WeaponFireSound != NULL)
		{
			//UGameplayStatics::PlaySoundAtLocation(this, WeaponFireSound, GetActorLocation());
			WeaponAudioComponent->SetSound(WeaponFireSound);
			WeaponAudioComponent->Play();
		}

		if (bSacrificeEnable)
		{
			if (SacrificeFireSound != NULL)
			{
				WeaponAudioComponent->SetSound(SacrificeFireSound);
				WeaponAudioComponent->Play();
			}
		}
		if (WeaponABP->GetClass()->ImplementsInterface(UAsylumWeaponInterface::StaticClass()))
		{
			IAsylumWeaponInterface::Execute_OnFire(WeaponABP);
		}

		AAsylumPlayerCharacter* PChar = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//The StartLocation of the raycast
		StartLocation = PChar->FollowCamera->GetComponentLocation();

		//The EndLocation of the raycast
		EndLocation = StartLocation + (PChar->FollowCamera->GetForwardVector() * WeaponRange);
		//UE_LOG(LogTemp, Warning, TEXT("Using Third Person Camera"));


	//Single line trace
		if (GetWorld()->LineTraceSingleByObjectType(SingleHit, StartLocation, EndLocation, ObjectsToTarget, CollisionParameters))
		{
			//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 5.0f, 5, 5.0f);
			//If we hit something and said target is what we are looking for
			if (SingleHit.bBlockingHit && IsValid(HitActor))
			{

				//Apply damage
				UGameplayStatics::ApplyPointDamage(HitActor, WeaponStatsData.DamageAmountSum, SingleHit.ImpactPoint, SingleHit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, WeaponStatsData.C_WeaponDamageType);

				this->Execute_OnHitTarget(this);
				if (WeaponStatsData.WeaponAmmoType == AT_Stun)
				{
					//Apply stamina damage - different characters will react differently to stamina loss

				}
			}
			CheckAmmo();
		}
	}
}

void AAsylumWeapon::FinishFire()
{
	CheckAmmo();
	if (WeaponStatsData.CurrentMagazineAmmo <= 0)
	{
		WeaponStatsData.CurrentMagazineAmmo = 0;
	}
	if (bIsAutomatic)
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimer);
	}
	if (bIsChargeWeapon || WeaponStatsData.WeaponAmmoType == AT_Charge || WeaponStatsData.WeaponAmmoType == AT_Stun)
	{
		FinishCharge();

		UE_LOG(LogTemp, Warning, TEXT("This should only print for charge weapons."))
	}
}

void AAsylumWeapon::StartCharge()
{
	//Play Charge SFX
	if (WeaponChargeFireSound != NULL)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, WeaponChargeFireSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
		WeaponAudioComponent->SetSound(WeaponChargeFireSound);
		WeaponAudioComponent->Play();
	}
	//Start timer for charge
	GetWorldTimerManager().SetTimer(ChargeTimer, this, &AAsylumWeapon::Charge, 0.01f, true);
	bIsCharging = true;
}

void AAsylumWeapon::Charge()
{
	if (bIsCharging)
	{
		//bCanWeaponFire = false;
		CurrentWeaponCharge = CurrentWeaponCharge + AmountToCharge;

		//This is temporary, will need to modify for balancing
		WeaponStatsData.DamageModifierAmount = CurrentWeaponCharge;
		if (CurrentWeaponCharge >= WeaponStatsData.WeaponChargeLimit)
		{
			CurrentWeaponCharge = WeaponStatsData.WeaponChargeLimit;
		}
	}
}

void AAsylumWeapon::FinishCharge()
{
	//Stop Timer
	GetWorldTimerManager().ClearTimer(ChargeTimer);
	bIsCharging = false;
	//Reset Charge value
	CurrentWeaponCharge = 0.f;
	//Reset Damage modifier
	WeaponStatsData.DamageModifierAmount = ChargeDamageModifer;
	//Attempt to apply damage
	Fire();

	//Play Fire SFX
	if (WeaponFireSound != NULL)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, WeaponFireSound, GetActorLocation());
		WeaponAudioComponent->SetSound(WeaponFireSound);
		WeaponAudioComponent->Play();
	}
}

void AAsylumWeapon::Reload()
{
	if (bIsReloading && !bIsWeaponEmpty)
	{
		//Prevent firing
		bCanWeaponFire = false;
		CurrentReloadTime = CurrentReloadTime + WeaponStatsData.ReloadSpeed;

		//Actually reload ammo
		if (CurrentReloadTime >= WeaponStatsData.MaxReloadTime)
		{
			WeaponStatsData.CurrentMagazineAmmo = WeaponStatsData.MaxMagazineAmmo;
			WeaponStatsData.CurrentWeaponClips--;
			FinishReload();

		}
	}
}

void AAsylumWeapon::StartReload()
{
	if (bCanReload)
	{
		if (WeaponReloadSound != NULL)
		{
			WeaponAudioComponent->SetSound(WeaponReloadSound);
			WeaponAudioComponent->Play();
		}
		bIsReloading = true;
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &AAsylumWeapon::Reload, WeaponStatsData.ReloadSpeed, true);
		if (WeaponABP->GetClass()->ImplementsInterface(UAsylumWeaponInterface::StaticClass()))
		{
			IAsylumWeaponInterface::Execute_OnStartReload(WeaponABP);
		}
	}
}

void AAsylumWeapon::FinishReload()
{
	if (bIsReloading)
	{
		bIsReloading = false;
		bCanWeaponFire = true;
		GetWorldTimerManager().ClearTimer(ReloadTimer);
		CurrentReloadTime = 0.0f;
		this->Execute_OnFinishReload(this);
		if (MyPawn->GetClass()->ImplementsInterface(UAsylumPlayerInterface::StaticClass()))
		{
			IAsylumPlayerInterface::Execute_OnPlayerReloadFinish(MyPawn);
		}
	}
}

float AAsylumWeapon::GetAmmoPercentage()
{
	float Percentage = WeaponStatsData.CurrentMagazineAmmo / WeaponStatsData.MaxWeaponClips;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

float AAsylumWeapon::GetReloadPercentage()
{
	float Percentage = CurrentReloadTime / WeaponStatsData.MaxReloadTime;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

float AAsylumWeapon::GetChargePercentage()
{
	float Percentage = CurrentWeaponCharge / WeaponStatsData.WeaponChargeLimit;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

void AAsylumWeapon::InfiniteAmmoToggle()
{
	if (!bEnableInfiniteAmmo)
	{
		WeaponStatsData.CurrentMagazineAmmo = 999;
		WeaponStatsData.CurrentWeaponClips = 999;
		bEnableInfiniteAmmo = true;
	}
	else
	{
		GiveWeaponFullAmmo();
	}
}

void AAsylumWeapon::UnlimitedClipsToggle()
{
	if (!bEnableNoClipLimit)
	{
		WeaponStatsData.CurrentWeaponClips = 999;
		bEnableNoClipLimit = true;
	}
	else
	{
		WeaponStatsData.CurrentWeaponClips = WeaponStatsData.MaxWeaponClips;
		bEnableNoClipLimit = false;
	}
}

void AAsylumWeapon::GodModeToggle()
{
	if (!bEnableGodMode)
	{
		WeaponStatsData.DamageModifierAmount = 999;
		InfiniteAmmoToggle();
		bEnableGodMode = true;
	}
	else
	{
		WeaponStatsData.DamageModifierAmount = WeaponStatsData.OriginalDamageModifier;
		InfiniteAmmoToggle();
		bEnableGodMode = false;
	}
}

void AAsylumWeapon::GiveWeaponFullAmmo()
{
	WeaponStatsData.CurrentMagazineAmmo = WeaponStatsData.MaxMagazineAmmo;
	WeaponStatsData.CurrentWeaponClips = WeaponStatsData.MaxWeaponClips;
}
