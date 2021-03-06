// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsylumDamageType.h"
#include "HellsAsylum.h"
#include "WeaponModComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AsylumWeaponAnimInstance.h"
#include "Components/AudioComponent.h"
#include "AsylumWeaponInterface.h"
#include "Components/ArrowComponent.h"
#include "AsylumWeapon.generated.h"

//What kind of weapon is this
UENUM(BlueprintType)
enum EWeaponType
{
	WT_Unequipped UMETA(DisplayName = "Unequipped"),
	WT_Pistol UMETA(DisplayName = "Pistol"),
	WT_SMG UMETA(DisplayName = "SMG"),
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
	WT_Dual_Pistol UMETA(DisplayName = "Dual Pistols"),
	WT_Dual_SMG UMETA(DisplayName = "Dual SMGs"),
	WT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	WT_Sniper UMETA(DisplayName = "Sniper Rifle")
};

//What slot should this weapon occupy
UENUM(BlueprintType)
enum EWeaponSlotType
{
	ST_None UMETA(DisplayName = "No Slot"),
	ST_Primary UMETA(DisplayName = "Slot One"),
	ST_Secondary UMETA(DisplayName = "Slot Two"),
	ST_Tertiary UMETA(DisplayName = "Slot Three"),
	ST_Quaternary UMETA(DisplayName = "Special Slot")
};

//What ammo does this weapon use
UENUM(BlueprintType)
enum EAmmoType
{
	AT_Standard UMETA(DisplayName = "Standard"),
	AT_Fire UMETA(DisplayName = "Incendiary"),
	AT_Ice UMETA(DisplayName = "Ice"),
	AT_Shock UMETA(DisplayName = "Shock"),
	AT_Grav UMETA(DisplayName = "Anti-Grav"),
	AT_Stun UMETA(DisplayName = "Paralyze"),
	AT_Energy UMETA(DisplayName = "Energy"),
	AT_Charge UMETA(DisplayName = "Charge"),
	AT_Explosive UMETA(DisplayName = "Explosive"),
	AT_Aragon UMETA(DisplayName = "Aragon")
};

//This is the data for this weapon (base damage, ammo, etc)
USTRUCT(BlueprintType)
struct FWeaponStatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//We use this to determine the slot the weapon should fill in the inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Data")
		TEnumAsByte<EWeaponType> WeaponType;

	//What is this weapon's slot type?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		TEnumAsByte<EWeaponSlotType> WeaponSlotType;

	//This weapon's Ammo Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Type")
		TEnumAsByte<EAmmoType> WeaponAmmoType;

	//Damage Type Object Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage Type")
		UAsylumDamageType* OR_WeaponDamageType = NULL;

	//Our Damage Type - Class Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage Type")
		TSubclassOf<UAsylumDamageType> C_WeaponDamageType;

	//What level is this weapon at?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 CurrentWeaponLevel = 1;


	//What is the maximum level of this weapon?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats|Level")
		int32 MaxWeaponLevel = 10;

	//How fast does this weapon fire - if it is automatic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float FireRate;

	///// Ammo



	//How much ammo should the player have in one clip/magazine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = "0"))
		float CurrentMagazineAmmo;

	//How much ammo should the weapon consume per shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int AmmoConsumptionAmount;

	//How much ammo should the player be able to hold with this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float CurrentWeaponClips;

	//Store the original MagAmmo for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Reset")
		float MaxMagazineAmmo;

	//Store the original WeaponClips count for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Reset")
		float MaxWeaponClips;

	//Max Reload Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload")
		float MaxReloadTime;

	//How fast can the player reload their weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload")
		float ReloadSpeed;




	////End Ammo

	///// Damage


	//How much damage does this weapon do, without any modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float BaseDamageAmount = 0.0f;
	//Are there any bonus to damage before Quicksilver or Overdrive? Otherwise, leave at 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float DamageMultiplierAmount = 0.0f;


	//When in Quicksilver or Overdrive, how much should the damage be multiplied by ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float DamageModifierAmount = 0.0f;

	//Give us the sum/product of BaseDamage and DamageMultiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage")
		float DamageAmountSum = 0.0f;

	//When in Quicksilver or Overdrive, how much should the damage be multiplied by?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Modifiers")
		float SpecialDamageMultiplier = 0.0f;

	//When the player hits an enemy at a weak point (IE Headshot), how much additional damage should the player deal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Modifiers")
		float CriticalHitMultiplier = 0.0f;

	//Store the original damage amount for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Reset")
		float OriginalBaseDamageAmount = 0.0f;

	//Store the original DamageMultiplier for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Damage|Reset")
		float OriginalDamageMultiplier = 0.0f;

	//Store the original DamageModifier for resetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Reset")
		float OriginalDamageModifier = 0.0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback")
		float WeaponFireLoudness = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback")
		float WeaponFireSoundRange = 0.0f;

	//How far does this weapon's "projectile" extend to?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Range")
		float WeaponDistanceRange = 0.0f;


	////End Damage



	////Start Charge

	//How much can this weapon charge up to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge")
		float WeaponChargeLimit;




};
/**
 * This is for getting the data for Weapon upgrades
 */
USTRUCT(BlueprintType)
struct FWeaponUpgradeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//What is the new level of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Level")
		int32 NewWeaponLevel;

	//How much additional damage gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Damage")
		float DamageUpgradeAmount;


	//How much faster can this weapon fire?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Damage")
		float FireRateUpgradeAmount;

	//How much additional range gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Damage")
		float WeaponRangeUpgradeAmount;

	//How much more ammo can the player hold in a single clip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Ammo")
		float MagazineCapacityUpgradeAmount;

	//How much ammo will the weapon now consume per shot?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Ammo")
		int32 AmmoConsumptionUpgradeAmount;

	//How many clips/mags of ammo can the player now hold?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Ammo")
		float MaxClipCapacityUpgradeAmount;

	//How much faster can charge weapons charge?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Charge")
		float ChargeWeaponAmountIncrease;

	//What is the new maximum limit for charge weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Charge")
		float ChargeLimitAmountIncrease;

	//How much additional reload speed gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Reload")
		float ReloadSpeedUpgradeAmount;

	//How much of the reload time is decreased
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Reload")
		float ReloadTimeReduceAmount;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade|Reload")
		float WeaponUpgradePrice;
};
UCLASS()
class HELLSASYLUM_API AAsylumWeapon : public AActor, public IAsylumWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsylumWeapon();

	//Current Reload Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload")
		float CurrentReloadTime;

	//Empty to hold weapon charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Charge")
		float CurrentWeaponCharge;

	//How much to charge the weapon by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge")
		float AmountToCharge;

	//What is the name of the socket that this weapon attaches to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FName WeaponAttachPoint;

	//What is the name of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FName WeaponName;

	//What is the image for the player's inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		UTexture2D* WeaponImage;

	//Can this weapon charge?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		bool bIsChargeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		bool bIsCharging;

	//Can this weapon charge?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		bool bCanWeaponFire;

	//Is this weapon automatic?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		bool bIsAutomatic;

	//Mainly for VFX - can also be used to spawn projectiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FName ProjectileSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* WeaponUpgradeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* WeaponStatsTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		struct FWeaponStatsData WeaponStatsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TMap<int32, FName> WeaponLevelMap;

	////Start Checks

//Is the current weapon's clip/player clip capacity depleted?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks|Ammo")
		bool bIsWeaponEmpty = false;

	//Is the player currently reloading?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks|Ammo")
		bool bIsReloading = false;

	//Has the player fired at least once?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks|Ammo")
		bool bCanReload = false;


	////End Checks

	//Start Feedback

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* OriginalWeaponFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* SacrificeFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponChargeFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponAltFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback|Audio")
		class USoundBase* WeaponDryFireSound;

	////End Feedback

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FName WeaponOwnerTag;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//	ACharacter* WeaponOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectsToTarget;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<AActor*> ActorsToIgnore;



	//This weapon's Original Ammo Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo|Type")
		TEnumAsByte<EAmmoType> OriginalWeaponAmmoType;

	//What is the price of this upgrade?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Upgrade")
		float NewWeaponUpgradePrice;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FHitResult SingleHit;

	UPROPERTY(BlueprintReadOnly)
		FVector MyLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
		FVector EndLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FHitResult> Hits;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Mesh")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon|Data")
		UAudioComponent* WeaponAudioComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Weapon|Data")
		UArrowComponent* FireArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ACharacter* WeaponOwner;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon|Data")
		bool bSacrificeEnable = false;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Weapon Mods")
		class UWeaponModComponent* WeaponModsComponent;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		float ChargeDamageModifer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		UAsylumDamageType* OriginalDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		TSubclassOf<UAsylumDamageType> C_OriginalDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		UAsylumDamageType* O_FireDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		UAsylumDamageType* O_IceDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		TSubclassOf<UAsylumDamageType> C_FireDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Damage")
		TSubclassOf<UAsylumDamageType> C_IceDamageType;

	

	class AAsylumCharacter* MyPawn;

public:

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void ActivateWeaponModInSlot(EWeaponOffenseModType ModSelected);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void DeactivateWeaponModInSlot(EWeaponOffenseModType ModSelected);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon|Cheats")
		bool bEnableInfiniteAmmo = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon|Cheats")
		bool bEnableNoClipLimit = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon|Cheats")
		bool bEnableGodMode = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon|Ammo")
		void GiveWeaponFullAmmo();


	UFUNCTION(BlueprintCallable, Category = "Weapon Reload")
		void CheckAmmo();


	UFUNCTION(BlueprintCallable, Category = "Weapon Attack")
		void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon Attack")
		void WeaponDryFire();

	UFUNCTION()
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon Attack")
		void FinishFire();

	UFUNCTION()
		void StartCharge();

	UFUNCTION()
		void Charge();

	UFUNCTION()
		void FinishCharge();

	UFUNCTION()
		void Reload();

	UFUNCTION(BlueprintCallable, Category = "Weapon Reload")
		void StartReload();
	UFUNCTION(BlueprintCallable, Category = "Weapon Reload")
		void FinishReload();


	FTimerHandle ChargeTimer;
	FTimerHandle ReloadTimer;
	FTimerHandle AutoFireTimer;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Ammo Percentage", Keywords = "Ammo"), Category = "Weapon|Stats")
		float GetAmmoPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Reload Percentage", Keywords = "Ammo"), Category = "Weapon|Stats")
		float GetReloadPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Charge Percentage", Keywords = "Ammo"), Category = "Weapon|Stats")
		float GetChargePercentage();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Cheats")
		void InfiniteAmmoToggle();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Cheats")
		void UnlimitedClipsToggle();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Cheats")
		void GodModeToggle();

	void AttachToOwner();
	void SetWeaponOwner(AAsylumCharacter* NewOwner);

private:

	UAnimInstance* WeaponABP;
	UAsylumWeaponAnimInstance* NewABP;

};
