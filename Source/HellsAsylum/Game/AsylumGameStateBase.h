// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/DataTable.h"
#include "UI/AsylumHUDInterface.h"
#include "AsylumGameStateBase.generated.h"

USTRUCT(BlueprintType)
struct FSaveableLevelEventData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	//This map will dictate what events need to be saved within a level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Events")
		TMap<FString, int32> LevelEventMap;

	//This holds references to enemies within the level who are still alive
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Data")
		TArray<AActor*> LevelEnemies;

	//This holds references to enemies within the level who are dead and should not be respawned
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Data")
		TArray<AActor*> LevelEnemiesDead;

};

USTRUCT(BlueprintType)
struct FMissionLevelStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	
	//This score is the threshold to beat for third place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		float ThirdPlaceMinimumScore = 0.0f;

	//This score is the last recorded amount that the player achieved for this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		float LastPlayerScore = 0.0f;

	//This score is the threshold to beat this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		float LevelMinimumScore = 0.0f;

	//This score is the threshold to beat for second place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		float SecondPlaceMinimumScore = 0.0f;

	//This score is the threshold to beat for first place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		float FirstPlaceMinimumScore = 0.0f;

	//This holds references to enemies within the level who are still alive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		TArray<AActor*> MissionEnemiesRemaining;

	//This holds references to enemies within the level who are dead and should not be respawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		TArray<AActor*> MissionEnemiesDead;
};

UCLASS()
class HELLSASYLUM_API AAsylumGameStateBase : public AGameStateBase, public IAsylumHUDInterface
{
	GENERATED_BODY()

public:

	//update save data's map when transitioning
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Data")
		TMap<FString, FSaveableLevelEventData> SaveableCampaignDataMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Data")
		TMap<FString, FMissionLevelStats> SaveableMissionDataMap;
		
	//Our Current Campaign Level's Event Data Struct - update save data's map when transitioning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Campaign")
		struct FSaveableLevelEventData CurrentCampaignLevelData;

	//Our Current Campaign Level's Event Data Struct - update save data's map when transitioning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		struct FMissionLevelStats CurrentMissionLevelData;


	UFUNCTION(BlueprintCallable, Category = "Level Data|Mission")
		void SetLevelScores(float LVMinScore, float TPScore, float SPScore, float FPScore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data|Mission")
		int EnemiesKilledCount = 0;
	
};
