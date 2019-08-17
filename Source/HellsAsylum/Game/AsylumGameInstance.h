// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AsylumDataCommInterface.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "AsylumGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AsylumGameInstance.generated.h"

//Tracks player story progression
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

//Container of important data to save
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		float SavedCurrentPlayerXP = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data|Campaign")
		float SavedPlayerXPLimit = 1000.0f;

	//How many points has the player gained throughout (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		float PlayerLifetimePoints_Campaign = 0.0f;



	//How many points has the player gained throughout (Mission)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerLifetimePoints_Mission = 0.0f;


	//How many Aragon Shards does the player have (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		int PlayerCurrentShardCount = 0;

	//How many Aragon Shards has the player gained throughout (Campaign)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Campaign")
		int PlayerLifetimeShardCount = 0;
};

//Saved Options values
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

	UAsylumGameInstance();

	

protected:

	//Did the player attempt to load a save file?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load Data")
		bool bWasSaveLoaded = false;

	//List of potential available save slot names
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TArray<FString> ManualSaveArray;

	//List of potential available auto save slot names
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TArray<FString> AutoSaveArray;

	//List of Campaign Level Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TArray<FSaveableLevelEventData> CampaignLevelEventsArray;

	//List of Mission Level Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		TArray<FMissionLevelStats> MissionLevelEventsArray;

	//Save Data Struct, container variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FSaveGameData SaveDataStruct;

	//Game Options Struct, container variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		struct FGameOptionsStruct SaveOptionsStruct;

	//The name of the current Save slot 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		FString CurrentSave = "";

	//What was the date/time the game was initiated
	//This is currently used for auto save checking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		FDateTime GameStartDate;

	//The name of the current Save slot - for Mission Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
		FString CurrentMissionSave = "";

	//Game Instance copy of PlayerStats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data|Player")
		struct FCharacterStatsData SavedPlayerCharacterStats;

	//Game Instance copy of Player Weapon Inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data|Player")
		TMap<int32, TSubclassOf<AAsylumWeapon>> SavedPlayerWeaponInventory;

	//Game Instance copy of Player Item Inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data|Player")
		TMap<int32, TSubclassOf<AItemBase>> SavedPlayerItemInventory;

	//Game Instance copy of Player Suit Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data|Player")
		struct FGoetheSuitStatsData SavedPlayerSuitStats;

	//Currently unused but may be necessary later
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data|Player")
		TMap<int, AAsylumWeapon*> SavedPlayerWeaponMap;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Campaign Data")
		FName GetCampaignDifficulty();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		float GetSavedCurrentXP();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		float GetSavedXPLimit();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		TMap<int32, TSubclassOf<AItemBase>> GetSavedItemInventory();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		TMap<int32, TSubclassOf<AAsylumWeapon>> GetSavedWeaponInventory();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		FCharacterStatsData GetSavedPlayerStats();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		FGoetheSuitStatsData GetSavedSuitStats();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Save Data")
		bool GetCurrentSaveStatus();

};
