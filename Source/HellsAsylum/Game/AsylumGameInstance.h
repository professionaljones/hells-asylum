// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AsylumDataCommInterface.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "AsylumGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AsylumGameInstance.generated.h"


UENUM(BlueprintType)
enum ECampaignModeActs
{
	CM_NoAct UMETA(DisplayName = "No Act"),
	CM_ActOne UMETA(DisplayName = "Act One"),
	CM_ActTwo UMETA(DisplayName = "Act Two"),
	CM_ActThree UMETA(DisplayName = "Act Three"),
	CM_ActFour UMETA(DisplayName = "Act Four"),
	CM_ActFive UMETA(DisplayName = "Act Five"),
	CM_Ending UMETA(DisplayName = "Epilogue"),
	CM_Bonus UMETA(DisplayName = "Aragon")


};

USTRUCT(BlueprintType)
struct FSaveGameData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	/*FSaveGameData()
	{}*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FDateTime SaveDate;

	//What act is the player currently on?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		TEnumAsByte<ECampaignModeActs> CurrentCampaignModeAct = CM_NoAct;

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
		FString SavedLevelName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		FTransform PlayerStartLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		FTransform PlayerSaveCheckpointLocation;

	//How many points has the player gained throughout (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		float PlayerLifetimePoints_Campaign = 0.0f;

	//How many points has the player gained throughout (Mission)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerLifetimePoints_Mission = 0.0f;

};

USTRUCT(BlueprintType)
struct FGameOptionsStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedMasterVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedMusicVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedWeaponVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedDialogueVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedEffectsVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedFootstepVolume = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data", meta = (ClampMin = "0", ClampMax = "1"))
		float SavedUIVolume = 0.0f;

	

};
UCLASS()
class HELLSASYLUM_API UAsylumGameInstance : public UGameInstance, public IAsylumDataCommInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FSaveGameData SaveDataStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FGameOptionsStruct SaveOptionsStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		FString CurrentSave = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load Data")
		bool bWasSaveLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FCharacterStatsData SavedPlayerCharacterStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AAsylumWeapon>> SavedPlayerWeaponInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, TSubclassOf<AItemBase>> SavedPlayerItemInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FGoetheSuitStatsData SavedPlayerSuitStats;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TMap<int, AAsylumWeapon*> SavedPlayerWeaponMap;
	
};
