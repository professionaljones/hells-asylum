// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsylumGameModeBase.generated.h"

UENUM(BlueprintType)
enum EGameType
{
	GT_UserInterface UMETA(DisplayName = "Main Menu Mode"),
	GT_Campaign UMETA(DisplayName = "Campaign Mode"),
	GT_MissionStandard UMETA(DisplayName = "Standard Mission Mode"),
	GT_MissionStealth UMETA(DisplayName = "Stealth Mission Mode"),
	GT_MissionAttack UMETA(DisplayName = "Score Attack Mission Mode"),
	GT_MissionSurvival UMETA(DisplayName = "Score Survival Mission Mode"),
	GT_BossRush UMETA(DisplayName = "Boss Rush Mode"),
	GT_Variety UMETA(DisplayName = "Variety Mission Mode")
};


UCLASS()
class HELLSASYLUM_API AAsylumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
		
public:

	AAsylumGameModeBase();

	//Difficulty Value - could be used as some kind of modifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode Data")
		float GameDifficulty = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode Data")
		TEnumAsByte<EGameType> CurrentGameType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode Data")
		bool bIsMissionMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode Data")
		TArray<AActor*> EnemiesArray;
};
