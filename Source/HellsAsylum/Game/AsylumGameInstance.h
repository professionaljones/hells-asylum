// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "AsylumGameStateBase.h"
#include "AsylumGameInstance.generated.h"


UENUM(BlueprintType)
enum ECampaignModeActs
{
	CM_ActOne UMETA(DisplayName = "Act One"),
	CM_ActTwo UMETA(DisplayName = "Act Two"),
	CM_ActThree UMETA(DisplayName = "Act Three"),
	CM_ActFour UMETA(DisplayName = "Act Four"),
	CM_ActFive UMETA(DisplayName = "Act Five")

};

USTRUCT(BlueprintType)
struct FSaveGameData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	/*FSaveGameData()
	{}*/

	//What act is the player currently on?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		TEnumAsByte<ECampaignModeActs> CurrentCampaignModeAct;

	//What difficulty setting did the player select?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
		int SavedGameDifficulty_Campaign = 2;

	//What difficulty setting did the player select?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
		int SavedGameDifficulty_Mission = 2;

	//How many points does the player have (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		float PlayerCurrentPoints_Campaign = 0.0f;

	//How many points does the player have (Mission)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerCurrentPoints_Mission = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
		TMap<FString, FSaveableLevelEventData> SaveableCampaignDataMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
		TMap<FString, FMissionLevelStats> SaveableMissionDataMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		FString SavedLevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		FTransform PlayerStartLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		FTransform PlayerSaveCheckpointLocation;

	//How many points has the player gained throughout (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		float PlayerLifetimePoints_Campaign;

	//How many points has the player gained throughout (Mission)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerLifetimePoints_Mission;

};
UCLASS()
class HELLSASYLUM_API UAsylumGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FSaveGameData SaveDataStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		FString CurrentSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load Data")
		bool bWasSaveLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FCharacterStatsData SavedPlayerCharacterStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FGoetheSuitStatsData SavedPlayerSuitStats;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FPlayerItemInvStruct SavedPlayerItemInv;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TMap<int, AAsylumWeapon*> SavedPlayerWeaponMap;
	
};
