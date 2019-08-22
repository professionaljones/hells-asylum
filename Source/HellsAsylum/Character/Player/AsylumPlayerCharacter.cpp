// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumPlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Kismet/KismetMathLibrary.h"

AAsylumPlayerCharacter::AAsylumPlayerCharacter()
{
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	MyScene->SetupAttachment(GetMesh(), GetMesh()->GetSocketBoneName("upperarm_rSocket"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	ThirdPersonCameraBoom = CreateDefaultSubobject<UAsylumSpringArmComponent>(TEXT("TP_CameraBoom"));
	ThirdPersonCameraBoom->SetupAttachment(RootComponent);

	ThirdPersonCameraBoom->BaseTargetArmLength = 350.0f;
	//Rotate the camera boom around the character
	ThirdPersonCameraBoom->bUsePawnControlRotation = true;

	//Create third person camera and attach to TP Boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(ThirdPersonCameraBoom, UAsylumSpringArmComponent::SocketName);
	//Camera remains in its original position at all time, does not rotate relative to boom
	FollowCamera->bUsePawnControlRotation = false;

	//Create stats component (contains health, shield and level values)
	CharacterStatsComponent = CreateDefaultSubobject<UAsylumStatsComponent>(TEXT("PlayerStatsComponent"));
	//Create suit component (contains suit data and powers)
	GoetheSuitComponent = CreateDefaultSubobject<UAsylumSuitComponent>(TEXT("GoetheSuitComponent"));
	//Create one audio component for character dialogue
	PlayerDialogueAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerDialogueAudioComponent"));
	//Create one audio component for hurt sounds
	PlayerSuitAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerSuitAudioComponent"));



	// set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;

}

bool AAsylumPlayerCharacter::GotMovementInput() const
{
	if (bGotForwardInput || bGotRightInput)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool AAsylumPlayerCharacter::IsSelectingTarget() const
{
	if (bStartLockOn)
	{
		return true;
	}
	else
	{
		return false;
	}

}

AActor* AAsylumPlayerCharacter::GetCurrentTarget() const
{
	if (IsValid(LockOnTarget))
	{
		return LockOnTarget;
	}
	else
		return nullptr;
}

FVector2D AAsylumPlayerCharacter::GetCurrentTargetSelectionInput() const
{
	return FVector2D();
}

void AAsylumPlayerCharacter::ActivateFlashlight()
{
	/*if (!bActivateFlashlight)
	{
		bActivateFlashlight = true;
		SuitLight->SetVisibility(bActivateFlashlight, false);
	}
	else
	{
		bActivateFlashlight = false;
		SuitLight->SetVisibility(bActivateFlashlight, false);
	}*/
}

void AAsylumPlayerCharacter::OnPlayerLevelUp()
{
	this->Execute_OnPlayerLevelUpEvent(this);
}

void AAsylumPlayerCharacter::OnPlayerModXP(float XPMod)
{
	if (CharacterStatsComponent)
	{
		//Update player XP amount
		CharacterStatsComponent->CurrentXP = CharacterStatsComponent->CurrentXP + XPMod;
		//Update UI
		this->Execute_PlayerUIUpdate(this);
		if (CharacterStatsComponent->CurrentXP >= CharacterStatsComponent->CurrentXPLimit)
		{
			OnPlayerLevelUp();
		}
	}
}

void AAsylumPlayerCharacter::EnableGodModeToggle()
{
	if (!bEnableGodMode)
	{
		//Set toggle bool to true
		bEnableGodMode = true;
		//Prevent player from taking damage
		this->bCanBeDamaged = false;
		//This is temporary - multiply movement by 3
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 3;
		//Additionally, give player infinite ammo
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->GodModeToggle();
		}
	}
	//Disable above
	else
	{
		bEnableGodMode = false;
		this->bCanBeDamaged = true;
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 3;
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->GodModeToggle();
		}
	}
}


void AAsylumPlayerCharacter::GrantFullHealth()
{
	//This can be used as a check for healing items or as a cheat
	CharacterStatsComponent->CharacterStatsDataStruct.fCurrentHealth = CharacterStatsComponent->CharacterStatsDataStruct.fMaxHealth;
	//Update UI
	this->Execute_PlayerUIUpdate(this);
}

void AAsylumPlayerCharacter::GrantFullShield()
{
	if (CharacterStatsComponent->CharacterStatsDataStruct.fMaxShield > 0.0f)
	{
		CharacterStatsComponent->CharacterStatsDataStruct.fCurrentShield = CharacterStatsComponent->CharacterStatsDataStruct.fMaxShield;
		if (!CharacterStatsComponent->CharacterStatsDataStruct.bHasShield)
		{
			CharacterStatsComponent->CharacterStatsDataStruct.bHasShield = true;
		}
	}

	//Update UI
	this->Execute_PlayerUIUpdate(this);
}

void AAsylumPlayerCharacter::GrantFullAragon()
{
	if (GoetheSuitComponent)
	{
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
		GoetheSuitComponent->SuitStatsData.CurrentAragonTanks = GoetheSuitComponent->SuitStatsData.MaxAragonTanks;
		this->Execute_PlayerUIUpdate(this);
	}
}

void AAsylumPlayerCharacter::GrantFullStats()
{
	GrantFullHealth();
	GrantFullShield();
	GrantFullAragon();
}

void AAsylumPlayerCharacter::PlayerJumpEvent()
{
	if (!bIsInCombat)
	{
		Jump();
	}
	else
	{
		bStartDodge = true;
		this->Execute_OnCharacterDodge(this, bStartDodge);
	}
}

void AAsylumPlayerCharacter::PlayerEndJump()
{
	if (!bIsInCombat)
	{
		StopJumping();
	}
	//else
	//{
	//	bStartDodge = false;
	//	this->Execute_OnCharacterDodge(this, bStartDodge);
	//}
}

void AAsylumPlayerCharacter::PlayerInteractRaycast()
{
	//Local Start Point of Ray
	FVector InteractStartLocation = FollowCamera->GetComponentLocation();
	//Local End Point of Ray
	FVector InteractEndLocation = InteractStartLocation + (FollowCamera->GetForwardVector() * 800.0f);
	//Local reference to detected Actor
	AActor* HitActor = InteractHitResult.GetActor();

	TArray<AActor*> ActorsToIgnore;
	
	//Single Line Trace
	/*if (UKismetSystemLibrary::LineTraceSingleForObjects(this, InteractStartLocation, InteractEndLocation, InteractableItems, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, InteractHitResult, true, FLinearColor::Blue, FLinearColor::White, 5.0f))
	{
		if (HitActor)
		{
			if (HitActor->GetClass()->ImplementsInterface(UAsylumInteractInterface::StaticClass()))
			{
				IAsylumInteractInterface::Execute_OnInteractEvent(HitActor);
			}
		}
	}*/

	if (UKismetSystemLibrary::LineTraceMultiForObjects(this, InteractStartLocation, InteractEndLocation, InteractableItems, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, InteractHitResults, true, FLinearColor::Blue, FLinearColor::White, 10.0f))
	{
		for (int32 i = 0; i < InteractHitResults.Num(); i++)
		{
			HitActor = InteractHitResults[i].GetActor();
			if (HitActor)
			{
				if (HitActor->GetClass()->ImplementsInterface(UAsylumInteractInterface::StaticClass()))
				{
					IAsylumInteractInterface::Execute_OnInteractEvent(HitActor);
				}
			}
		}
	}

	////DEBUG: for some reason the value isn't cleared when called again for a different actor
	//if (HitActor)
	//{
	//	HitActor = NULL;
	//}
}

void AAsylumPlayerCharacter::ActivateMainAbility()
{
	EGoetheMainAbilities PlayerSelectedAbility = GoetheSuitComponent->SuitStatsData.GoetheSelectedMainAbility;
	CheckAragonStatus();
	if (GoetheSuitComponent->bEnableMainAbility)
	{
		if (!GoetheSuitComponent->bStartMainAbility)
		{
			if (PlayerSelectedAbility == MA_Quicksilver)
			{
				ActivateQuicksilver();

			}
			if (PlayerSelectedAbility == MA_Overdrive)
			{
				ActivateOverdrive();
			}
			if (PlayerSelectedAbility == MA_Sacrifice)
			{
				ActivateSacrifice();
			}
		}
		else
		{
			DeactivateMainAbility();
		}
	}
}

void AAsylumPlayerCharacter::ActivatePassivePower(EGoethePassivePowers PowerToUse)
{
	if (GoetheSuitComponent)
	{
		if (PowerToUse == PP_AHR)
		{

		}
		if (PowerToUse == PP_Reload)
		{

		}
		if (PowerToUse == PP_Cooler)
		{

		}
	}
}

void AAsylumPlayerCharacter::DeactivateMainAbility()
{
	EGoetheMainAbilities PlayerSelectedAbility = GoetheSuitComponent->SuitStatsData.GoetheSelectedMainAbility;
	if (GoetheSuitComponent->bEnableMainAbility)
	{
		if (GoetheSuitComponent->bStartMainAbility)
		{
			if (PlayerSelectedAbility == MA_Quicksilver)
			{
				DeactivateQuicksilver();
			}
			if (PlayerSelectedAbility == MA_Overdrive)
			{
				DeactivateOverdrive();
			}
			if (PlayerSelectedAbility == MA_Sacrifice)
			{
				DeactivateSacrifice();
			}
		}

	}

}

void AAsylumPlayerCharacter::ActivateSelectedPower(EGoetheActivePowers PowerSelected)
{
	if (PowerSelected == AP_DespairOrb)
	{
		SpawnDespairOrb(GoetheSuitComponent->SuitStatsData.DespairOrbCurrentLevel);
	}
	if (PowerSelected == AP_HarmonyOrb)
	{
		SpawnHarmonyOrb(GoetheSuitComponent->SuitStatsData.HarmonyOrbCurrentLevel);
	}
	if (PowerSelected == AP_Tractor)
	{
		GetWorldTimerManager().SetTimer(TractorHandle, this, &AAsylumPlayerCharacter::ItemTractorBeam, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), true);
	}
}

void AAsylumPlayerCharacter::ActivatePowerOne()
{
	if (GoetheSuitComponent)
	{
		EGoetheActivePowers PowerSelected = GoetheSuitComponent->SuitStatsData.GoetheActivePowerOne;
		if (PowerSelected == AP_DespairOrb)
		{
			SpawnDespairOrb(GoetheSuitComponent->SuitStatsData.DespairOrbCurrentLevel);
		}
		if (PowerSelected == AP_HarmonyOrb)
		{
			SpawnHarmonyOrb(GoetheSuitComponent->SuitStatsData.HarmonyOrbCurrentLevel);
		}
	}
}

void AAsylumPlayerCharacter::ActivatePowerTwo()
{
	if (GoetheSuitComponent)
	{
		EGoetheActivePowers PowerSelected = GoetheSuitComponent->SuitStatsData.GoetheActivePowerTwo;
		if (PowerSelected == AP_DespairOrb)
		{
			SpawnDespairOrb(GoetheSuitComponent->SuitStatsData.DespairOrbCurrentLevel);
		}
		if (PowerSelected == AP_HarmonyOrb)
		{
			SpawnHarmonyOrb(GoetheSuitComponent->SuitStatsData.HarmonyOrbCurrentLevel);
		}
	}
}

void AAsylumPlayerCharacter::ActivatePowerThree()
{
	if (GoetheSuitComponent)
	{
		EGoetheActivePowers PowerSelected = GoetheSuitComponent->SuitStatsData.GoetheActivePowerThree;
		if (PowerSelected == AP_Tractor)
		{
			GetWorldTimerManager().SetTimer(TractorHandle, this, &AAsylumPlayerCharacter::ItemTractorBeam, 0.01f, true);
		}
	}
}

void AAsylumPlayerCharacter::DeactivatePowerThree()
{
	if (GoetheSuitComponent)
	{
		EGoetheActivePowers PowerSelected = GoetheSuitComponent->SuitStatsData.GoetheActivePowerThree;
		if (PowerSelected == AP_Tractor)
		{
			GetWorldTimerManager().ClearTimer(TractorHandle);
		}
	}
}

void AAsylumPlayerCharacter::DeactivateSelectedPower(EGoetheActivePowers PowerUsed)
{
	if (PowerUsed == AP_Tractor)
	{
		GetWorldTimerManager().ClearTimer(TractorHandle);
	}
}

void AAsylumPlayerCharacter::SpawnDespairOrb(int DiscordPowerLevel)
{
	FActorSpawnParameters SpawnParameters;

	FRotator SpawnRotation = PCon->GetControlRotation();
	if (CurrentWorld)
	{

		switch (DiscordPowerLevel)
		{
		case 1:
			CurrentWorld->SpawnActor<ABaseOrb>(DespairLVOne, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 2:
			CurrentWorld->SpawnActor<ABaseOrb>(DespairLVTwo, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 3:
			CurrentWorld->SpawnActor<ABaseOrb>(DespairLVThree, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		}
	}

}

void AAsylumPlayerCharacter::SpawnHarmonyOrb(int HarmonyPowerLevel)
{
	FActorSpawnParameters SpawnParameters;
	FRotator SpawnRotation = PCon->GetControlRotation();
	if (CurrentWorld)
	{
		switch (HarmonyPowerLevel)
		{
		case 1:
			CurrentWorld->SpawnActor<ABaseOrb>(HarmonyLVOne, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 2:
			CurrentWorld->SpawnActor<ABaseOrb>(HarmonyLVTwo, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 3:
			CurrentWorld->SpawnActor<ABaseOrb>(HarmonyLVThree, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		}
	}
}

void AAsylumPlayerCharacter::ActivateQuicksilver()
{
	if (GoetheSuitComponent->bEnableMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = true;
		if (GoetheSuitComponent->bStartMainAbility)
		{
			CustomTimeDilation = GoetheSuitComponent->SuitStatsData.QuicksilverPlayerSpeed;
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GoetheSuitComponent->SuitStatsData.QuicksilverSlowDownAmount);
			if (IsValid(CurrentEquippedWeapon))
			{
				CurrentEquippedWeapon->Execute_OnDamageModify(CurrentEquippedWeapon);
				GetWorldTimerManager().SetTimer(QuickSilverHandle, this, &AAsylumPlayerCharacter::OnQuicksilverConsumption, 0.01f, true);
			}
		}
	}
}

void AAsylumPlayerCharacter::ActivateSacrifice()
{
	if (GoetheSuitComponent->bEnableMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = true;
		GetWorldTimerManager().SetTimer(SacrificeHandle, this, &AAsylumPlayerCharacter::UpdateSacrificeStatus, 0.01, false);
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->bSacrificeEnable = true;
		}
	}
}

void AAsylumPlayerCharacter::RechargeAragonTanks()
{
	if (GoetheSuitComponent->bStartGaugeRecharge && !GoetheSuitComponent->bStartMainAbility)
	{
		this->Execute_UpdateAragonUI(this);
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge + GoetheSuitComponent->SuitStatsData.AragonRegenAmount;
		if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge >= GoetheSuitComponent->SuitStatsData.MaxAragonGauge)
		{

			if (GoetheSuitComponent->SuitStatsData.CurrentAragonTanks < GoetheSuitComponent->SuitStatsData.MaxAragonTanks)
			{
				GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = 0.0f;
				GoetheSuitComponent->SuitStatsData.CurrentAragonTanks++;
			}
			if (GoetheSuitComponent->SuitStatsData.CurrentAragonTanks >= GoetheSuitComponent->SuitStatsData.MaxAragonTanks)
			{
				GoetheSuitComponent->SuitStatsData.CurrentAragonTanks = GoetheSuitComponent->SuitStatsData.MaxAragonTanks;
				GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
				GetWorldTimerManager().ClearTimer(RechargeAragonHandle);
				GoetheSuitComponent->bStartMainAbility = false;
				GoetheSuitComponent->bStartGaugeRecharge = false;
				this->Execute_UpdateAragonUI(this);
				if (PlayerSuitAudioComponent->Sound != TanksRechargedSound)
				{
					PlayerSuitAudioComponent->Sound = TanksRechargedSound;
				}
				PlayerSuitAudioComponent->Play(0.0f);
			}
		}

	}

}

void AAsylumPlayerCharacter::OnQuicksilverConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		ConsumeAragon(GoetheSuitComponent->SuitStatsData.QuicksilverConsumptionRate);
	}
}

void AAsylumPlayerCharacter::OnOverdriveConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		ConsumeAragon(GoetheSuitComponent->SuitStatsData.OverdriveConsumptionRate);
		CheckAragonStatus();
	}
}

void AAsylumPlayerCharacter::OnSacrificeConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		CharacterStatsComponent->CharacterStatsDataStruct.fCurrentHealth = CharacterStatsComponent->CharacterStatsDataStruct.fCurrentHealth - GoetheSuitComponent->SuitStatsData.SacrificeConsumptionRate;
		UpdateSacrificeStatus();
	}
}


void AAsylumPlayerCharacter::ItemTractorBeam()
{	
	FHitResult ItemHitResult;
	AActor* HitActor = ItemHitResult.GetActor();
	TArray<AActor*> ActorsToIgnore;
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, StartLocation, EndLocation, GoetheSuitComponent->SuitStatsData.ScanRadius, Items, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, ItemHitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f))
	{
		if (HitActor && !HitActor->ActorHasTag("MajorUpgrade"))
		{
			FVector NewItemLocation = UKismetMathLibrary::VInterpTo(HitActor->GetActorLocation(), StartLocation, UGameplayStatics::GetWorldDeltaSeconds(this), 5.0f);
			if (HitActor->SetActorLocation(NewItemLocation, true, nullptr, ETeleportType::None) == true)
			{
				UE_LOG(LogTemp, Verbose, TEXT("Item is moving!"));
			}
			
			
		}
	}
}

void AAsylumPlayerCharacter::PlayerEnergyDrain()
{
	FVector DrainEndLocation = GetActorLocation() + (GetActorLocation() * 3000.0f);
	TArray<FHitResult> DrainHitResults;
	//int32 DrainHitLength = DrainHitResults.Max();
//	AActor* HitActor = DrainHitResult.GetActor();
	TArray<AActor*> ActorsToIgnore;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this, GetActorLocation(), DrainEndLocation, GoetheSuitComponent->SuitStatsData.EnemySearchRadius, DrainEnemyArray, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, DrainHitResults, true, FLinearColor::Red, FLinearColor::Blue, 5.0f))
	{
		for (int32 i = 0; i < DrainHitResults.Max(); i++)
		{
			if (DrainHitResults[i].GetActor())
			{
				UGameplayStatics::ApplyDamage(DrainHitResults[i].GetActor(), 5.0f, PCon, this, NULL);
				this->Execute_OnRecoverHealth(this, UGameplayStatics::ApplyDamage(DrainHitResults[i].GetActor(), 5.0f, PCon, this, NULL));
			}
		}
	}
}

void AAsylumPlayerCharacter::EquipWeaponOne()
{
	if (WeaponSlotOne)
	{
		EquipWeapon(WeaponSlotOne);
		//NewWeaponSlot = WeaponSlotOneKey;
	}
}

void AAsylumPlayerCharacter::EquipWeaponTwo()
{
	if (WeaponSlotTwo)
	{
		EquipWeapon(WeaponSlotTwo);
		//NewWeaponSlot = WeaponSlotTwoKey;
	}
}

void AAsylumPlayerCharacter::EquipWeaponThree()
{
	if (WeaponSlotThree)
	{
		EquipWeapon(WeaponSlotThree);
		//NewWeaponSlot = WeaponSlotThreeKey;
	}
}

void AAsylumPlayerCharacter::HolsterWeapon()
{
	Super::HolsterWeapon();
	this->Execute_PlayerUIUpdate(this);
	this->Execute_OnWeaponEquip(this, WT_Unequipped);
	//bUseControllerRotationYaw = false;

}

void AAsylumPlayerCharacter::EquipWeapon(AAsylumWeapon* NewWeapon)
{
	Super::EquipWeapon(NewWeapon);
	//CurrentWeaponInventory.Add(NewWeaponSlot, NewWeapon);
	//bUseControllerRotationYaw = true;
}

void AAsylumPlayerCharacter::CharacterSprint()
{
	bIsSprintButtonDown = !bIsSprintButtonDown;
	Super::CharacterSprint();
	if (bIsSprintButtonDown)
	{
		bIsRunning = true;
		Super::CharacterSprint();
	}
	else
	{
		bIsRunning = false;
		Super::CharacterSprint();
	}
	
}

void AAsylumPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//SetupFlashLight();
	
	/*TanksEmptySound = LoadObject<USoundBase>(nullptr, TEXT("SoundCue'/Game/Static/ArtAssets/SFX/Powers/Ar_TanksEmpty_Cue.Ar_TanksEmpty_Cue'"));
	TanksRechargedSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Static/ArtAssets/SFX/Powers/Power_Bar_Refilled.Power_Bar_Refilled'"));*/
}

void AAsylumPlayerCharacter::MoveForward(float Value)
{
	bGotForwardInput = (Controller != NULL) && (Value != 0.0f);
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (bGotForwardInput)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
			if (!bIsCrouched)
			{
				MakeNoise(CharacterStatsComponent->CharacterStatsDataStruct.fMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), CharacterStatsComponent->CharacterStatsDataStruct.fMovementMaxRange, PlayerTag);
			}
			else
			{
				MakeNoise(CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange, PlayerTag);
			}
		}
	}
}

void AAsylumPlayerCharacter::MoveRight(float Value)
{
	bGotRightInput = (Controller != NULL) && (Value != 0.0f);
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (bGotRightInput)
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
			if (!bIsCrouched)
			{
				MakeNoise(CharacterStatsComponent->CharacterStatsDataStruct.fMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), CharacterStatsComponent->CharacterStatsDataStruct.fMovementMaxRange, PlayerTag);
			}
			else
			{
				MakeNoise(CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange, PlayerTag);
			}
		}
	}
}

void AAsylumPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAsylumPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAsylumPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//Action Bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAsylumPlayerCharacter::PlayerJumpEvent);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAsylumPlayerCharacter::PlayerEndJump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AAsylumPlayerCharacter::OnWeaponAttack);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAsylumPlayerCharacter::PlayerInteractRaycast);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AAsylumPlayerCharacter::OnWeaponStop);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AAsylumPlayerCharacter::OnWeaponReload);
	PlayerInputComponent->BindAction("Holster", IE_Pressed, this, &AAsylumPlayerCharacter::HolsterWeapon);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAsylumPlayerCharacter::CharacterSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AAsylumPlayerCharacter::CharacterSprint);
	//PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &AAsylumPlayerCharacter::ActivateFlashlight);
	PlayerInputComponent->BindAction("Activate Main Ability", IE_Pressed, this, &AAsylumPlayerCharacter::ActivateMainAbility);
	//PlayerInputComponent->BindAction("Activate Main Ability", IE_Released, this, &AAsylumPlayerCharacter::DeactivateMainAbility);
	PlayerInputComponent->BindAction("Activate Power One", IE_Pressed, this, &AAsylumPlayerCharacter::ActivatePowerOne);
	PlayerInputComponent->BindAction("Activate Power Two", IE_Pressed, this, &AAsylumPlayerCharacter::ActivatePowerTwo);
	PlayerInputComponent->BindAction("Activate Power Three", IE_Pressed, this, &AAsylumPlayerCharacter::ActivatePowerThree);
	PlayerInputComponent->BindAction("Activate Power Three", IE_Released, this, &AAsylumPlayerCharacter::DeactivatePowerThree);
	PlayerInputComponent->BindAction("Select Primary Weapon One", IE_Pressed, this, &AAsylumPlayerCharacter::EquipWeaponOne);
	PlayerInputComponent->BindAction("Select Primary Weapon Two", IE_Pressed, this, &AAsylumPlayerCharacter::EquipWeaponTwo);
	PlayerInputComponent->BindAction("Select Secondary Weapon", IE_Pressed, this, &AAsylumPlayerCharacter::EquipWeaponThree);

	//Axis Bindings

	PlayerInputComponent->BindAxis("MoveForward", this, &AAsylumPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAsylumPlayerCharacter::MoveRight);



	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAsylumPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AAsylumPlayerCharacter::LookUpAtRate);
}

void AAsylumPlayerCharacter::ConsumeAragon(float AmountToConsume)
{
	GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge - AmountToConsume;
	CheckAragonStatus();
}

void AAsylumPlayerCharacter::ActivateOverdrive()
{
	if (!GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = true;
		CustomTimeDilation = GoetheSuitComponent->SuitStatsData.QuicksilverPlayerSpeed;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GoetheSuitComponent->SuitStatsData.QuicksilverSlowDownAmount);
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.SpecialDamageMultiplier;
			GetWorldTimerManager().SetTimer(QuickSilverHandle, this, &AAsylumPlayerCharacter::OnOverdriveConsumption, GoetheSuitComponent->SuitStatsData.QuicksilverConsumptionRate, true);
		}
	}
}

void AAsylumPlayerCharacter::DeactivateQuicksilver()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = false;
		CustomTimeDilation = 1;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
		GetWorldTimerManager().ClearTimer(QuickSilverHandle);
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->Execute_RecalculateBaseWeaponDamage(CurrentEquippedWeapon);
		}
	}
}

void AAsylumPlayerCharacter::DeactivateOverdrive()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		CustomTimeDilation = 1;
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.OriginalDamageModifier;
		}
		GoetheSuitComponent->bStartMainAbility = false;
		GetWorldTimerManager().ClearTimer(OverdriveHandle);
	}
}

void AAsylumPlayerCharacter::DeactivateSacrifice()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = false;
		GetWorldTimerManager().ClearTimer(SacrificeHandle);
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.OriginalDamageModifier;
			CurrentEquippedWeapon->bSacrificeEnable = false;
		}
	}
}

void AAsylumPlayerCharacter::CheckAragonStatus()
{
	this->Execute_UpdateAragonUI(this);
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge <= GoetheSuitComponent->SuitStatsData.MaxAragonGauge)
	{
		if (!GoetheSuitComponent->bStartGaugeRecharge)
		{
			GoetheSuitComponent->bStartGaugeRecharge = true;
			GetWorldTimerManager().SetTimer(RechargeAragonHandle, this, &AAsylumPlayerCharacter::RechargeAragonTanks, GoetheSuitComponent->SuitStatsData.AragonRegenSpeed, true);
		}
		if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge <= 0.0f && GoetheSuitComponent->SuitStatsData.CurrentAragonTanks > 0.0f)
		{
			GoetheSuitComponent->SuitStatsData.CurrentAragonTanks--;
			GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
		}
	}
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonTanks <= 0.0f)
	{
		///Maybe on harder difficulties we turn off the automatic recharge? - B. Jones
		/*GoetheSuitComponent->bStartGaugeRecharge = false;
		GetWorldTimerManager().ClearTimer(RechargeAragonHandle);*/
		if (!GoetheSuitComponent->bStartGaugeRecharge)
		{
			GoetheSuitComponent->bStartGaugeRecharge = true;
			GetWorldTimerManager().SetTimer(RechargeAragonHandle, this, &AAsylumPlayerCharacter::RechargeAragonTanks, GoetheSuitComponent->SuitStatsData.AragonRegenSpeed, true);
		}
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = 0.0f;
		GoetheSuitComponent->SuitStatsData.CurrentAragonTanks = 0.0f;
		if (GoetheSuitComponent->bStartMainAbility)
		{
			DeactivateMainAbility();
			if (PlayerSuitAudioComponent->Sound != TanksEmptySound)
			{
				PlayerSuitAudioComponent->Sound = TanksEmptySound;
			}
			PlayerSuitAudioComponent->Play(0.0f);
			//GoetheSuitComponent->bStartMainAbility = false;

		}
	}
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge >= GoetheSuitComponent->SuitStatsData.MaxAragonGauge && GoetheSuitComponent->SuitStatsData.CurrentAragonTanks >= GoetheSuitComponent->SuitStatsData.MaxAragonTanks)
	{
		GoetheSuitComponent->bStartGaugeRecharge = false;
		GetWorldTimerManager().ClearTimer(RechargeAragonHandle);
	}
}

void AAsylumPlayerCharacter::UpdateSacrificeStatus()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount + GoetheSuitComponent->SuitStatsData.SacrificeConsumptionRate;
		if (CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount >= GoetheSuitComponent->SuitStatsData.SacrificePowerLimit)
		{
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = GoetheSuitComponent->SuitStatsData.SacrificePowerLimit;
		}
	}
}

void AAsylumPlayerCharacter::SetupFlashLight()
{
	/*SuitLight->AttenuationRadius = 800.0f;
	SuitLight->InnerConeAngle = 22.0f;*/
}

void AAsylumPlayerCharacter::OnWeaponAttack()
{
	if (CurrentEquippedWeapon)
	{
		CurrentEquippedWeapon->StartFire();
		this->Execute_OnWeaponFire(this, CurrentEquippedWeapon->WeaponStatsData.WeaponType);
		this->Execute_PlayerUIUpdate(this);
	}
}

void AAsylumPlayerCharacter::OnWeaponStop()
{
	if (CurrentEquippedWeapon)
	{
		CurrentEquippedWeapon->FinishFire();
		CurrentEquippedWeapon->Execute_OnFinishFire(CurrentEquippedWeapon);
		//this->Execute_PlayerUIUpdate(this);
	}
}

void AAsylumPlayerCharacter::OnWeaponReload()
{
	if (CurrentEquippedWeapon)
	{
		CurrentEquippedWeapon->StartReload();
		this->Execute_OnPlayerReload(this);
	}
}
