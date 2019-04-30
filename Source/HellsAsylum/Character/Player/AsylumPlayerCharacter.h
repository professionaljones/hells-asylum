// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Interfaces/AsylumPlayerInterface.h"
#include "HellsAsylum.h"
#include "Items/ItemBase.h"
#include "Character/Interfaces/AsylumInteractInterface.h"
#include "GameComponents/Character/AsylumSuitComponent.h"
#include "Weapons/SuitAbilities/BaseOrb.h"
#include "Components/SceneComponent.h"
#include "GameComponents/AsylumSpringArmComponent.h"
#include "Character/AsylumCharacter.h"
#include "AsylumPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class HELLSASYLUM_API AAsylumPlayerCharacter : public AAsylumCharacter, public IAsylumPlayerInterface, public IAsylumInteractInterface
{
	GENERATED_BODY()

public:
	AAsylumPlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	//Base Arm Length for TP Camera Boom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float TP_BaseArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		FVector OrbSpawnLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AItemBase>> ItemInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AAsylumWeapon>> PlayerWeaponInventory;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Camera")
		bool bShouldSwapShoulder = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Movement")
		bool bIsCrouchButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Weapon")
		bool bIsAimButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Movement")
		bool bIsJumpButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Movement")
		bool bIsSprintButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Powers")
		bool bIsPowerOneActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Powers")
		bool bIsPowerTwoActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Powers")
		bool bIsPowerThreeActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Powers")
		bool bIsMainAbilityActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Gamepad")
		bool bIsLeftShoulderButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Gamepad")
		bool bIsRightShoulderButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Cheats")
		bool bEnableGodMode = false;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Player Health Percentage", Keywords = "Health"), Category = "Character|Stats")
		float GetPlayerHealthPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Player Shield Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetPlayerShieldPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Player Aragon Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetPlayerAragonPercentage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> DespairLVOne;

	UFUNCTION(BlueprintCallable, Category = "Player|Powers")
		void ItemTractorBeam();

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	FName PlayerTag = "Attacker";


	virtual bool GotMovementInput() const override;

	virtual bool IsSelectingTarget() const override;
	virtual AActor* GetCurrentTarget() const override;
	virtual FVector2D GetCurrentTargetSelectionInput() const override;

public:

	UFUNCTION(BlueprintCallable, Category = "Cheats")
		void EnableGodModeToggle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAudioComponent* PlayerDialogueAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAudioComponent* PlayerSuitAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player|Stats")
		class UAsylumStatsComponent* PlayerStatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player|Stats")
		class UAsylumSuitComponent* GoetheSuitComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAsylumSpringArmComponent* ThirdPersonCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class USceneComponent* MyScene;

	//FTimerHandle LockOnHandle;


	//UFUNCTION(BlueprintCallable, Category = "Player|Actions")
	//	void LockOnToTarget();



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotThree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* LastWeaponEquipped;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
		bool bStartLockOn = false;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullHealth();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullShield();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullStats();



	/**
	 * Called via input to activate the selected Main Ability
	 * @param PlayerSelectedAbility this is the Ability we want to Activate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility);

	/**
	 * Called via input to deactivate the selected Main Ability
	 * @param PlayerSelectedAbility this is the Ability we want to Deactivate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateMainAbility(EGoetheMainAbilities PlayerSelectedAbility);

	/**
	 * Called via input to Activate the player's desired power to use
	 * @param PowerSelected this is the Power we want to Activate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateSelectedPower(EGoetheActivePowers PowerSelected);

	/**
	 * Called via input to stop the power in use
	 * @param PowerSelected this is the Power we want to Deactivate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateSelectedPower(EGoetheActivePowers PowerUsed);

	//Allows the player to activate the Quicksilver power
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void SpawnDiscordOrb(int DiscordPowerLevel);

	//Allows the player to activate the Quicksilver power
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateQuicksilver();

	//Allows the player to activate the Sacrifice power
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateSacrifice();

	//This function will allow the suit's Aragon Tank(s) to fill up to the max guage limit
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void RechargeAragonTanks();

	//This function controls how much Aragon is consumed when Quicksilver is activated
	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void OnQuicksilverConsumption();

	//This function controls how much Aragon is consumed when Overdrive is activated
	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void OnOverdriveConsumption();

	//This function controls how much HEALTH is consumed when Sacrifice is activated
	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void OnSacrificeConsumption();



	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void ConsumeAragon(float AmountToConsume);


	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateOverdrive();

	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateQuicksilver();

	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateOverdrive();

	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateSacrifice();


	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void CheckAragonStatus();

	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void UpdateSacrificeStatus();

	FTimerHandle OverdriveHandle;
	FTimerHandle RechargeAragonHandle;
	FTimerHandle QuickSilverHandle;
	FTimerHandle SacrificeHandle;
private:
	bool bGotForwardInput;
	bool bGotRightInput;

};
