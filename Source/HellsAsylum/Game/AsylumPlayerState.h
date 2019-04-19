// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AslyumMissionModeInterface.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "AsylumPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumPlayerState : public APlayerState, public IAslyumMissionModeInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
		FCharacterStatsData CachedCharacterStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
		FTransform PlayerStartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
		FTransform PlayerCheckpointLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		int PlayerLives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerCurrentScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerCurrentScoreMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerCriticalHitMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float ScoreMultiplierTimeLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data|Mission")
		float PlayerBoostDropChance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Data")
		struct FCharacterStatsData CharacterStatsDataStruct;

	UFUNCTION(BlueprintCallable, Category = "Player Data")
		void CachePlayerStats();
};
