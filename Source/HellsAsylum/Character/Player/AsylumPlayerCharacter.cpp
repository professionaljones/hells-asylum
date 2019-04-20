// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumPlayerCharacter.h"

AAsylumPlayerCharacter::AAsylumPlayerCharacter()
{
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
//	ItemInvComponent = CreateDefaultSubobject<UAsylumPlayerInventoryComponent>(TEXT("PlayerItemInventory"));
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

AActor * AAsylumPlayerCharacter::GetCurrentTarget() const
{
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

void AAsylumPlayerCharacter::LockOnToTarget()
{
	
	if (!bStartLockOn)
	{
		GetWorldTimerManager().SetTimer(LockOnHandle, this, &AAsylumCharacter::LockOn, 0.01f, true);
		bStartLockOn = true;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(LockOnHandle);
		bStartLockOn = false;
	}

	
}

void AAsylumPlayerCharacter::ActivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility)
{
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

void AAsylumPlayerCharacter::DeactivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility)
{
	if (GoetheSuitComponent->bEnableMainAbility)
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
				CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.SpecialDamageMultiplier;
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
	if (GoetheSuitComponent->bStartGaugeRecharge)
	{
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge + GoetheSuitComponent->SuitStatsData.AragonRegenAmount;

	}
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge >= GoetheSuitComponent->SuitStatsData.MaxAragonGauge)
	{
		GoetheSuitComponent->bStartGaugeRecharge = false;
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
	}
	
}

void AAsylumPlayerCharacter::OnQuicksilverConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge - GoetheSuitComponent->SuitStatsData.QuicksilverConsumptionRate;
		CheckAragonStatus();

	}
}

void AAsylumPlayerCharacter::OnOverdriveConsumption()
{
	if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge - GoetheSuitComponent->SuitStatsData.OverdriveConsumptionRate;
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
	return Percentage;
}

float AAsylumPlayerCharacter::GetPlayerShieldPercentage()
{
	float Percentage = PlayerStatsComponent->CharacterStatsDataStruct.fCurrentShield / PlayerStatsComponent->CharacterStatsDataStruct.fMaxShield;
	return Percentage;
}

float AAsylumPlayerCharacter::GetPlayerAragonPercentage()
{
	float Percentage = GoetheSuitComponent->SuitStatsData.CurrentAragonGauge / GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
	return Percentage;
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

void AAsylumPlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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
	if (GoetheSuitComponent->bStartMainAbility)
	{
		GoetheSuitComponent->bStartMainAbility = false;
		CustomTimeDilation = GoetheSuitComponent->SuitStatsData.OverdriveSpeedBoost;
		if (IsValid(CurrentEquippedWeapon))
		{
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.SpecialDamageMultiplier;
			GetWorldTimerManager().SetTimer(OverdriveHandle, this, &AAsylumPlayerCharacter::OnOverdriveConsumption, 0.01f, true);
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
			CurrentEquippedWeapon->WeaponStatsData.DamageModifierAmount = CurrentEquippedWeapon->WeaponStatsData.OriginalDamageModifier;
			
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
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge <= GoetheSuitComponent->SuitStatsData.CurrentAragonGauge)
	{
		GoetheSuitComponent->bStartGaugeRecharge = true;
		GetWorldTimerManager().SetTimer(RechargeAragonHandle, this, &AAsylumPlayerCharacter::RechargeAragonTanks, GoetheSuitComponent->SuitStatsData.AragonRegenSpeed, true);
	}
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonGauge <= 0.0f)
	{
		GoetheSuitComponent->SuitStatsData.CurrentAragonTanks--;
		GoetheSuitComponent->SuitStatsData.CurrentAragonGauge = GoetheSuitComponent->SuitStatsData.MaxAragonGauge;
	}
	if (GoetheSuitComponent->SuitStatsData.CurrentAragonTanks <= 0)
	{
		GoetheSuitComponent->bStartGaugeRecharge = false;
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
