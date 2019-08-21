// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumCharacter.h"
#include "Player/AsylumPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAsylumCharacter::AAsylumCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockOnActorsToIgnore.Add(this);
	//TValidLockOnObjects.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
}

float AAsylumCharacter::GetHealthPercentage()
{
	if (CharacterStatsComponent)
	{
		return CharacterStatsComponent->CharacterStatsDataStruct.fCurrentHealth / CharacterStatsComponent->CharacterStatsDataStruct.fMaxHealth;
	}
	else
	{
		return 0.0f;
	}
}

float AAsylumCharacter::GetShieldPercentage()
{
	if (CharacterStatsComponent)
	{
		return CharacterStatsComponent->CharacterStatsDataStruct.fCurrentShield / CharacterStatsComponent->CharacterStatsDataStruct.fMaxShield;
	}
	else
	{
		return 0.0f;
	}
}

float AAsylumCharacter::GetAragonPercentage()
{
	if (GoetheSuitComponent)
	{
		return GoetheSuitComponent->SuitStatsData.CurrentAragonGauge / GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
	}
	else
	{
		return 0.0f;
	}
}

// Called when the game starts or when spawned
void AAsylumCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void AAsylumCharacter::EquipWeapon(AAsylumWeapon* NewWeapon)
{
	if (NewWeapon != NULL)
	{
		if (CurrentEquippedWeapon)
		{
			CurrentEquippedWeapon->SetActorHiddenInGame(false);
			CurrentEquippedWeapon = NULL;

		}
		CurrentEquippedWeapon = NewWeapon;
		CurrentEquippedWeapon->SetWeaponOwner(this);
		CurrentEquippedWeapon->AttachToOwner();
		this->Execute_OnWeaponEquip(this, CurrentEquippedWeapon->WeaponStatsData.WeaponType);
		
		bIsInCombat = true;
	}
}

void AAsylumCharacter::HolsterWeapon()
{
	bIsInCombat = false;
	if (CurrentEquippedWeapon)
	{	
		CurrentEquippedWeapon->SetActorHiddenInGame(true);
		CurrentEquippedWeapon = NULL;
	}
}

void AAsylumCharacter::CharacterSprint()
{
	//bIsRunning = !bIsRunning;

	if (bIsRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterRunSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = CharacterWalkSpeed;
	}
}

// Called every frame
void AAsylumCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAsylumCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAsylumCharacter::IsInCombat() const
{
	AAsylumPlayerController* PCon = Cast<AAsylumPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(CurrentEquippedWeapon))
	{
		if (bIsInCombat)
		{
			//bIsInCombat = true;
			return true;
		}
		else
		{
			return false;
		}

	}

	return false;

}

bool AAsylumCharacter::IsSelectingTarget() const
{
	return false;
}

AActor* AAsylumCharacter::GetCurrentTarget() const
{
	return nullptr;
}

FVector2D AAsylumCharacter::GetCurrentTargetSelectionInput() const
{
	return FVector2D();
}

//void AAsylumCharacter::LockOn()
//{
//	AAsylumPlayerController* PCon = Cast<AAsylumPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
//	FVector StartLocation = FollowCamera->GetComponentLocation();
//	FVector ForwardVectorMod = FollowCamera->GetForwardVector() * fMaxLockOnDistance;
//	FVector EndLocation = StartLocation + ForwardVectorMod;
//	FHitResult LockOnHitResult;
//	FRotator PlayerStartRotator = PCon->GetControlRotation();
//	FRotator NewRotation;
//	AActor* HitActor = LockOnHitResult.GetActor();
//
//	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, StartLocation, EndLocation, fLockOnRadius, TValidLockOnObjects, true, LockOnActorsToIgnore, EDrawDebugTrace::ForDuration, LockOnHitResult, true, FLinearColor::Blue, FLinearColor::Yellow, 5.0f))
//	{
//		if (LockOnHitResult.bBlockingHit && IsValid(HitActor))
//		{
//			
//		}
//	}
//}

