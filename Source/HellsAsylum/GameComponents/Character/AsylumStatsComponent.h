// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Items/ItemBase.h"
#include "HellsAsylum.h"
#include "Weapons/AsylumWeapon.h"
#include "AsylumStatsComponent.generated.h"

//This struct holds the Character upgrade data, though this may no longer be necessary
USTRUCT(BlueprintType)
struct FCharacterUpgradeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	//What is the new level of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Upgrade|Level")
		int NewCharacterLevel;

	//How much additional health gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Upgrade|Stats")
		float HealthUpgradeAmount;

	//How much additional Shield gained at this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Upgrade|Stats")
		float ShieldUpgradeAmount;

};

USTRUCT(BlueprintType)
struct FCharacterStatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Shield")
		bool bHasShield;

	//How much health does the character currently have?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Health")
		float fCurrentHealth = 200.0f;


	//How much health can the player have?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Health")
		float fMaxHealth = 200.0f;


	//How much shield does the character currently have?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Shield")
		float fCurrentShield = 0.0f;

	//How much shield can the character have?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Shield")
		float fMaxShield = 0.0f;

	//This is used to upgrade enemies for balancing - for player, new game/NGP
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Level")
		int iCurrentCharacterLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Level")
		int iMaxCharacterLevel = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float fMovementLoudness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float fMovementMaxRange = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float fCrouchMovementLoudness = 0.75f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float fCrouchMovementMaxRange = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AAsylumWeapon>> WeaponInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AItemBase>> ItemInventory;


	//Resistances

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Resistances")
		float fFireResist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Resistances")
		float fIceResist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Resistances")
		float fShockResist;


	////////////// End of Player Stats




};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLSASYLUM_API UAsylumStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAsylumStatsComponent();

	////////// Player Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Health")
		bool bIsCharacterDead;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
		struct FCharacterStatsData CharacterStatsDataStruct;


	//// Start Weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AAsylumWeapon *WeaponEquipped;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Player")
		FTransform PlayerStartTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats|Player")
		FTransform PlayerCheckpointTransform;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable *CharacterDataTable;
};
