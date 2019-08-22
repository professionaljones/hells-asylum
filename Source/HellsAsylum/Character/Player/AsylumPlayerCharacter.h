// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Interfaces/AsylumPlayerInterface.h"
#include "HellsAsylum.h"
#include "Items/ItemBase.h"
#include "Character/Interfaces/AsylumInteractInterface.h"
#include "AsylumPlayerController.h"
#include "Weapons/SuitAbilities/BaseOrb.h"
#include "Components/SceneComponent.h"
#include "GameComponents/AsylumSpringArmComponent.h"
#include "Character/AsylumCharacter.h"
#include "AsylumPlayerCharacter.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerUpdateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUIBarDelegate, FName, BarID, float, NewPercentage);

UCLASS()
class HELLSASYLUM_API AAsylumPlayerCharacter : public AAsylumCharacter, public IAsylumPlayerInterface, public IAsylumInteractInterface
{
	GENERATED_BODY()

public:
	AAsylumPlayerCharacter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, EditAnywhere, BlueprintReadWrite, Category = "Player")
		FPlayerUpdateDelegate UpdatePlayerData;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Player")
		FUpdateUIBarDelegate UpdateStatBar;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	//Base Arm Length for TP Camera Boom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float TP_BaseArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		FVector OrbSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AItemBase>> ItemInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Weapon")
		TMap<int32, TSubclassOf<AAsylumWeapon>> PlayerWeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Weapon")
		TMap<int32, class AAsylumWeapon*> CurrentWeaponInventory;

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



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Interact")
		TArray<TEnumAsByte<EObjectTypeQuery>> InteractableItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Interact")
		TArray<TEnumAsByte<EObjectTypeQuery>> DrainEnemyArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> DespairLVOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> DespairLVTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> DespairLVThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> HarmonyLVOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> HarmonyLVTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Powers")
		TSubclassOf<ABaseOrb> HarmonyLVThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat")
		AActor* LockOnTarget = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Player|Powers")
		void ItemTractorBeam();

	UFUNCTION(BlueprintCallable, Category = "Player|Powers")
		void PlayerEnergyDrain();

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
		virtual AActor* GetCurrentTarget() const override;

protected:

	

	void EquipWeaponOne();
	void EquipWeaponTwo();
	void EquipWeaponThree();

	virtual void HolsterWeapon() override;
	virtual void EquipWeapon(AAsylumWeapon* NewWeapon) override;
	virtual void CharacterSprint() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	FVector StartLocation = GetActorLocation();
	FHitResult InteractHitResult;
	TArray<FHitResult> InteractHitResults;

	FVector EndLocation = StartLocation + StartLocMult;
	FVector StartLocMult = StartLocation * 2000.0f;


	virtual bool GotMovementInput() const override;

	virtual bool IsSelectingTarget() const override;

	virtual FVector2D GetCurrentTargetSelectionInput() const override;
	AAsylumPlayerController* PCon = Cast<AAsylumPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UWorld* CurrentWorld = GetWorld();

	UFUNCTION(BlueprintCallable, Category = "Player|Suit")
		void ActivateFlashlight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Input|Aux")
		bool bActivateFlashlight = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SFX)
		TSoftObjectPtr<USoundBase> EmptyTankSO;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SFX)
		class USoundBase* TanksEmptySound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SFX)
		class USoundBase* TanksRechargedSound;

	UFUNCTION(BlueprintCallable, Category = "Player|Experience")
		void OnPlayerLevelUp();

	UFUNCTION(BlueprintCallable, Category = "Player|Experience")
		void OnPlayerModXP(float XPMod);

	//These points determine player strength - power recharge limits, strengths, etc
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Upgrade")
		int32 CurrentSuitPowerPoints = 0;

	//These points determine player capacity - weapon slots, max ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Upgrade")
		int32 CurrentSuitCapacityPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Upgrade")
		//These points determine misc player stats - movement noise
		int32 CurrentSuitAuxPoints;

	int32 WeaponSlotOneKey = 1;
	int32 WeaponSlotTwoKey = 2;
	int32 WeaponSlotThreeKey = 3;
	int32 NewWeaponSlot = 0;

public:

	UFUNCTION(BlueprintCallable, Category = "Cheats")
		void EnableGodModeToggle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAudioComponent* PlayerDialogueAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAudioComponent* PlayerSuitAudioComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player|Stats")
		class UAsylumStatsComponent* PlayerStatsComponent;*/



		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class UAsylumSpringArmComponent* ThirdPersonCameraBoom;

	//Spawn point for certain Goethe powers
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player")
		class USceneComponent* MyScene;

	//Reference to weapon in Slot One
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotOne;

	//Reference to weapon in Slot Two
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotTwo;

	//Reference to weapon in Slot Three
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Weapon")
		class AAsylumWeapon* WeaponSlotThree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
		bool bStartLockOn = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
		bool bStartDodge = false;

	//Called to give player full health
	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullHealth();

	//Called to give player full shield
	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullShield();

	//Called to give player full aragon capacity
	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullAragon();

	//Called to give player full health, shield and aragon
	UFUNCTION(BlueprintCallable, Category = "Player")
		void GrantFullStats();

	//Called via input to tell anim BP to Jump or Dodge
	UFUNCTION(BlueprintCallable, Category = "Player")
		void PlayerJumpEvent();

	//Called via input to tell anim BP to Stop Jump or Dodge
	UFUNCTION(BlueprintCallable, Category = "Player")
		void PlayerEndJump();

	//Called via input to interact with detected object
	UFUNCTION(BlueprintCallable, Category = "Player")
		void PlayerInteractRaycast();



	/**
	 * Called via input to activate the selected Main Ability
	 * @param PlayerSelectedAbility this is the Ability we want to Activate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivateMainAbility();

	/**
	 * Called via input to deactivate the selected Main Ability
	 * @param PlayerSelectedAbility this is the Ability we want to Deactivate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateMainAbility();

	/**
	 * Called via input to Activate the player's desired power to use
	 * @param PowerSelected this is the Power we want to Activate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void ActivateSelectedPower(EGoetheActivePowers PowerSelected);

	//Called via input to Activate Power One
	//Desired power is a local variable that is set to first power value
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void ActivatePowerOne();

	//Called via input to Activate Power Two
	//Desired power is a local variable that is set to second power value
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void ActivatePowerTwo();

	//Called via input to Activate Power Three
	//Desired power is a local variable that is set to third power value
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void ActivatePowerThree();

	//Called via input to Deactivate Power Three
	//Desired power is a local variable that is set to third power value
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void DeactivatePowerThree();

	/**
	 * Called via input to stop the power in use
	 * @param PowerSelected this is the Power we want to Deactivate
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void DeactivateSelectedPower(EGoetheActivePowers PowerUsed);

	/**
	 * Called via Activate Power function to spawn desired Despair Orb
	 * @param DespairPowerLevel - Ensure that spawn the right level of Orb
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void SpawnDespairOrb(int DespairPowerLevel);

	/**
	 * Called via Activate Power function to spawn desired Harmony Orb
	 * @param HarmonyPowerLevel - Ensure that spawn the right level of Orb
	 */
	UFUNCTION(BlueprintCallable, Category = "Suit|Powers")
		void SpawnHarmonyOrb(int HarmonyPowerLevel);

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


	//This function will subtract Aragon from the player's Aragon guage
	//@param AmountToConsume How much do we want to subtract from the player per unit of time
	UFUNCTION(BlueprintCallable, Category = "Suit|Usage")
		void ConsumeAragon(float AmountToConsume);

	//This function will activate the player's selected Passive Power(s)
	//@param PowerToUse Which power do we want to use
	UFUNCTION(BlueprintCallable, Category = "Suit|Abilities")
		void ActivatePassivePower(EGoethePassivePowers PowerToUse);


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
	FTimerHandle InteractHandle;
	FTimerHandle TractorHandle;
private:
	void SetupFlashLight();

	bool bGotForwardInput;
	bool bGotRightInput;

	void OnWeaponAttack();
	void OnWeaponStop();
	void OnWeaponReload();

};
