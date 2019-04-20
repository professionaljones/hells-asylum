// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "AsylumSuitComponent.generated.h"


UENUM(BlueprintType)
enum EGoetheMainAbilities
{
	MA_None UMETA(DisplayName = "Unequipped"),
	MA_Quicksilver UMETA(DisplayName = "Quicksilver"),
	MA_Overdrive UMETA(DisplayName = "Overdrive"),
	MA_Sacrifice UMETA(DisplayName = "Sacrifice"),
	MA_Overload UMETA(DisplayName = "Overload")
};

UENUM(BlueprintType)
enum EGoetheActivePowers
{
	AP_None UMETA(DisplayName = "Unequipped"),
	AP_DoubleShot UMETA(DisplayName = "Weapon Double Shot Attack"),
	AP_Grenade UMETA(DisplayName = "Weapon Grenade"),
	AP_WeaponCharge UMETA(DisplayName = "Weapon Charge Attack"),
	AP_Tractor UMETA(DisplayName = "Attractor"),
	AP_Drain UMETA(DisplayName = "Energy Drain"),
	AP_DespairOrb UMETA(DisplayName = "Despair Orbs"),
	AP_HarmonyOrb UMETA(DisplayName = "Harmony Orbs"),
	AP_Tesla UMETA(DisplayName = "Tesla Cyclone"),
	AP_Charge UMETA(DisplayName = "Super Charger"),
	AP_Snow UMETA(DisplayName = "Snow Storm")

};

UENUM(BlueprintType)
enum EGoethePassivePowers
{
	PP_None UMETA(DisplayName = "Unequipped"),
	PP_Reload UMETA(DisplayName = "Reload Speed Upgrade"),
	PP_Damage UMETA(DisplayName = "Damage Upgrade"),
	PP_MainAbility UMETA(DisplayName = "Power Optimizer"),
	PP_Cooler UMETA(DisplayName = "Suit Boost"),
	PP_SpaceJump UMETA(DisplayName = "Double Jump Boots"),
	PP_JetBoots UMETA(DisplayName = "Jump Jets")

};

UENUM(BlueprintType)
enum EGoetheSuitType
{
	ST_Standard UMETA(DisplayName = "Standard Suit"),
	ST_Evo UMETA(DisplayName = "Evolution Suit"),
	ST_Revenge UMETA(DisplayName = "Revenge Suit"),
	ST_Ascension UMETA(DisplayName = "Ascension Suit"),
	ST_Varia UMETA(DisplayName = "Varia Suit")
};

//This struct holds the Character Suit upgrade data, though this may no longer be necessary
USTRUCT(BlueprintType)
struct FGoetheSuitStatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:



	//Main Abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		TEnumAsByte<EGoetheMainAbilities> GoetheSelectedMainAbility;

	//Available Suit Types for Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit")
		TEnumAsByte<EGoetheSuitType> GoetheSuitType;

	//Passive Power Slot One
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Passive Powers")
		TEnumAsByte<EGoethePassivePowers> GoethePassivePowerOne;

	//Passive Power Slot Two
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Passive Powers")
		TEnumAsByte<EGoethePassivePowers> GoethePassivePowerTwo;

	//Passive Power Slot For Double Jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Passive Powers")
		TEnumAsByte<EGoethePassivePowers> GoethePassivePowerBoots;

	//Passive Power Slot For Jump Jets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Passive Powers")
		TEnumAsByte<EGoethePassivePowers> GoethePassivePowerJet;

	//Active Power Slot One - Left Arm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Powers")
		TEnumAsByte<EGoetheActivePowers> GoetheActivePowerOne;

	//Active Power Slot Two - Right Arm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Powers")
		TEnumAsByte<EGoetheActivePowers> GoetheActivePowerTwo;

	//Active Power Slot Three - Body
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Powers")
		TEnumAsByte<EGoetheActivePowers> GoetheActivePowerThree;

	//Despair Orb Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int DespairOrbCurrentLevel;

	//Despair Orb Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int DespairOrbMaxLevel;

	//Harmony Orb Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int HarmonyOrbCurrentLevel;

	//Harmony Orb Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int HarmonyOrbMaxLevel;

	//Tesla Cyclone Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int TeslaCurrentLevel;

	//Tesla Cyclone Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int TeslaMaxLevel;

	//Supercharger Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int ChargerCurrentLevel;

	//Supercharger Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int ChargerMaxLevel;

	//Snow Storm Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int StormCurrentLevel;

	//Snow Storm Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int StormMaxLevel;

	//Tractor Beam Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int TractorCurrentLevel;

	//Tractor Beam Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int TractorMaxLevel;

	//Energy Drain Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int EnergyDrainCurrentLevel;

	//Energy Drain Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int EnergyDrainMaxLevel;

	//Weapon Powers Current Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels", meta = (ClampMin = "1"))
		int WeaponPowersCurrentLevel;

	//Weapon Powers Max Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Power Levels")
		int WeaponPowersMaxLevel;


	////Start Stats


	//What is the current amount of the player's Main Ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities", meta = (ClampMin = "1"))
		float CurrentAragonGauge;


	// What is the limit of the player's Main Ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities")
		float MaxAragonGauge;

	//How many Main Ability tanks does the player currently have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities")
		float CurrentAragonTanks;

	//How much does the suit's aragon guage recharge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit")
		float AragonRegenAmount;
	//How fast does the suit's aragon guage recharge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit")
		float AragonRegenSpeed;

	//How many Main Ability tanks can the player currently have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities")
		float MaxAragonTanks;


	/**
* How much should Quicksilver affect the world?
*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Quicksilver")
		float QuicksilverSlowDownAmount;



	//How much should Quicksilver affect the player?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Quicksilver")
		float QuicksilverPlayerSpeed;


	//How much power should Quicksilver consume per second?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Quicksilver")
		float QuicksilverConsumptionRate;


	//How much power should Overdrive consume per second?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Overdrive")
		float OverdriveConsumptionRate;

	//How much health should Sacrifice consume per second?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Sacrifice")
		float SacrificeConsumptionRate;

	//How much power should Sacrifice grant before diminishing returns?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Sacrifice")
		float SacrificePowerLimit;

	//How much should Overdrive affect the player?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Main Abilities|Overdrive")
		float OverdriveSpeedBoost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float EnergyDrainConsumptionRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float DiscordAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float HarmonyAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float SnowAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float ChargerAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float DrainAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float TeslaAbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Cooldown")
		float WeaponAbilityCooldown;

	//Scan radius - how far should the player be able to pull in items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Tractor")
		float ScanRadius;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers|Abilities|Drain")
		float EnemySearchRadius;

	///End Stats

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLSASYLUM_API UAsylumSuitComponent : public UActorComponent
{
	GENERATED_BODY()

		UAsylumSuitComponent();

public:

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Suit")
		struct FGoetheSuitStatsData SuitStatsData;

	//Start/Stop recharge for aragon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		bool bStartGaugeRecharge = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit")
		bool bEnablePowers = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit")
		bool bEnableMainAbility = false;

	/**
	* Enable Main Ability when pressed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		bool bStartMainAbility;

	/**
	* Enable Ability 1 when pressed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		bool bStartAbilityOneCooldown;

	/**
	* Enable Ability 2 when pressed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		bool bStartAbilityTwoCooldown;

	/**
	* Enable Ability 3 when pressed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		bool bStartAbilityThreeCooldown;



	//Suit Upgrades



	/**
	* How fast should the player be able to reload their weapons
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Arms")
		float ReloadSpeedIncrease;




	//Feedback



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* QuicksilverStart;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* QuicksilverEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* OverdriveStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* OverdriveEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* RechargeComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* AragonTanksEmpty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* DiscordOrbImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* HarmonyOrbImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* ChargerImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* TeslaImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* DrainImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* TractorImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		UTexture2D* StormImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText DiscordAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText HarmonyAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText ChargerAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText TeslaAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText DrainAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText TractorAbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
		FText StormAbilityName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		float AbilityOneCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		float AbilityTwoCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suit|Abilities")
		float AbilityThreeCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable *SuitStatsDataTable;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//void FindAsset();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;






		
};
