// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Character/AsylumCharacter.h"
#include "AsylumCharacterAI.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumCharacterAI : public AAsylumCharacter
{
	GENERATED_BODY()

		

public:
	// Sets default values for this character's properties
	AAsylumCharacterAI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player|Stats")
		class UAsylumStatsComponent* EnemyStatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Campaign|AI|Feedback")
		float f_CampaignPointsToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|AI|")
		float MaxVisionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|AI|")
		float VisionFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Campaign|AI|Feedback")
		float f_MissionPointsToAdd;

	UFUNCTION(BlueprintCallable, Category = "AI|Attack")
		void EnemyWeaponFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|AI")
		class USceneComponent* RaycastLocationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Stats|AI")
		FName CharacterName;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Character Health Percentage", Keywords = "Health"), Category = "Character|Stats")
		float GetAIHealthPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Character Shield Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetAIShieldPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Character Aragon Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetAIAragonPercentage();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Weapon|AI")
		TSubclassOf<AAsylumWeapon> AI_WeaponToEquip;
	
};
