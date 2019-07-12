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

	PlayerStatsComponent = CreateDefaultSubobject<UAsylumStatsComponent>(TEXT("PlayerStatsComponent"));
	GoetheSuitComponent = CreateDefaultSubobject<UAsylumSuitComponent>(TEXT("GoetheSuitComponent"));
	PlayerDialogueAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerDialogueAudioComponent"));
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
	return false;
}

bool AAsylumPlayerCharacter::IsSelectingTarget() const
{
	return false;
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

void AAsylumPlayerCharacter::EnableGodModeToggle()
{
	if (!bEnableGodMode)
	{
		bEnableGodMode = true;
		this->bCanBeDamaged = false;
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 3;
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->GodModeToggle();
		}
	}
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
	PlayerStatsComponent->CharacterStatsDataStruct.fCurrentHealth = PlayerStatsComponent->CharacterStatsDataStruct.fMaxHealth;
	this->Execute_PlayerUIUpdate(this);
}

void AAsylumPlayerCharacter::GrantFullShield()
{
	PlayerStatsComponent->CharacterStatsDataStruct.fCurrentShield = PlayerStatsComponent->CharacterStatsDataStruct.fMaxShield;
	if (!PlayerStatsComponent->CharacterStatsDataStruct.bHasShield)
	{
		PlayerStatsComponent->CharacterStatsDataStruct.bHasShield = true;
	}
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
	}
}

void AAsylumPlayerCharacter::PlayerEndJump()
{
	if (!bIsInCombat)
	{
		StopJumping();
	}
	else
	{
		bStartDodge = false;
	}
}

void AAsylumPlayerCharacter::PlayerInteractRaycast()
{
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector EndLocation = FollowCamera->GetComponentLocation() + (FollowCamera->GetComponentLocation() * 800.0f);
	FHitResult InteractHitResult;

	TSubclassOf<UAsylumInteractInterface> InteractInterface;
	AActor* HitActor = InteractHitResult.GetActor();
	TArray<AActor*> ActorsToIgnore;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(this, StartLocation, EndLocation, InteractableItems, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, InteractHitResult, true, FLinearColor::Blue, FLinearColor::White, 5.0f))
	{

		if (HitActor)
		{
			//PCon->Execute_OnInteractVisible(PCon);
			this->Execute_OnInteractVisible(this);
		}
	}
	else
	{
		//this->Execute_
	}

}

void AAsylumPlayerCharacter::ActivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility)
{
	CheckAragonStatus();
	if (GoetheSuitComponent->bEnableMainAbility)
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

void AAsylumPlayerCharacter::DeactivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility)
{
	if (GoetheSuitComponent->bEnableMainAbility)
	{
		//CheckAragonStatus();
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
	if (World)
	{

		switch (DiscordPowerLevel)
		{
		case 1:
			World->SpawnActor<ABaseOrb>(DespairLVOne, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 2:
			World->SpawnActor<ABaseOrb>(DespairLVTwo, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 3:
			World->SpawnActor<ABaseOrb>(DespairLVThree, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		}
	}

}

void AAsylumPlayerCharacter::SpawnHarmonyOrb(int HarmonyPowerLevel)
{
	FActorSpawnParameters SpawnParameters;
	FRotator SpawnRotation = PCon->GetControlRotation();
	if (World)
	{
		switch (HarmonyPowerLevel)
		{
		case 1:
			World->SpawnActor<ABaseOrb>(HarmonyLVOne, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 2:
			World->SpawnActor<ABaseOrb>(HarmonyLVTwo, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
			break;
		case 3:
			World->SpawnActor<ABaseOrb>(HarmonyLVThree, MyScene->GetComponentLocation(), SpawnRotation, SpawnParameters);
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
			}
		}

	}

}

void AAsylumPlayerCharacter::OnQuicksilverConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		ConsumeAragon(GoetheSuitComponent->SuitStatsData.QuicksilverConsumptionRate);
		//CheckAragonStatus();

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
		PlayerStatsComponent->CharacterStatsDataStruct.fCurrentHealth = PlayerStatsComponent->CharacterStatsDataStruct.fCurrentHealth - GoetheSuitComponent->SuitStatsData.SacrificeConsumptionRate;
		UpdateSacrificeStatus();
	}
}

float AAsylumPlayerCharacter::GetPlayerHealthPercentage()
{
	float Percentage = PlayerStatsComponent->CharacterStatsDataStruct.fCurrentHealth / PlayerStatsComponent->CharacterStatsDataStruct.fMaxHealth;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

float AAsylumPlayerCharacter::GetPlayerShieldPercentage()
{
	float Percentage = PlayerStatsComponent->CharacterStatsDataStruct.fCurrentShield / PlayerStatsComponent->CharacterStatsDataStruct.fMaxShield;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

float AAsylumPlayerCharacter::GetPlayerAragonPercentage()
{
	float Percentage = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge / GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
	if (Percentage >= 0)
	{
		return Percentage;
	}
	else
		return 0.0f;
}

void AAsylumPlayerCharacter::ItemTractorBeam()
{
	FVector EndLocation = GetActorLocation() + (GetActorLocation() * 3000.0f);
	FHitResult ItemHitResult;
	AActor* HitActor = ItemHitResult.GetActor();
	TArray<AActor*> ActorsToIgnore;
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, GetActorLocation(), EndLocation, GoetheSuitComponent->SuitStatsData.ScanRadius, Items, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, ItemHitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f))
	{
		if (HitActor)
		{


		}
	}
}

void AAsylumPlayerCharacter::PlayerEnergyDrain()
{
	FVector EndLocation = GetActorLocation() + (GetActorLocation() * 3000.0f);
	TArray<FHitResult> DrainHitResults;
	//int32 DrainHitLength = DrainHitResults.Max();
//	AActor* HitActor = DrainHitResult.GetActor();
	TArray<AActor*> ActorsToIgnore;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this, GetActorLocation(), EndLocation, GoetheSuitComponent->SuitStatsData.EnemySearchRadius, DrainEnemyArray, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, DrainHitResults, true, FLinearColor::Red, FLinearColor::Blue, 5.0f))
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
				MakeNoise(PlayerStatsComponent->CharacterStatsDataStruct.fMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), PlayerStatsComponent->CharacterStatsDataStruct.fMovementMaxRange, PlayerTag);
			}
			else
			{
				MakeNoise(PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange, PlayerTag);
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
				MakeNoise(PlayerStatsComponent->CharacterStatsDataStruct.fMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), PlayerStatsComponent->CharacterStatsDataStruct.fMovementMaxRange, PlayerTag);
			}
			else
			{
				MakeNoise(PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), GetActorLocation(), PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange, PlayerTag);
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
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAsylumPlayerCharacter::PlayerJumpEvent);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAsylumPlayerCharacter::PlayerEndJump);

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
		//CheckAragonStatus();
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
	this->Execute_PlayerUIUpdate(this);
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
			DeactivateMainAbility(GoetheSuitComponent->SuitStatsData.GoetheSelectedMainAbility);
			//GoetheSuitComponent->bStartMainAbility = false;

		}
	}
	/*if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->bStartGaugeRecharge = false;
	}*/
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
