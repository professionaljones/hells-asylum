// Copyright 2019 Property of Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

//#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HellsAsylum.h"
#include "AsylumDataCommInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAsylumDataCommInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumDataCommInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnPlayerLoadFromSave(bool bWasSaveLoaded);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnGameModeStart(bool bIsMissionMode);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Campaign")
		void OnCampaignEnemyDeath(float f_PointsToAdd);


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnMissionEnemyDeath(float f_PointsToAdd);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Campaign")
		void OnAddEnemyToDatabase(bool bFirstTimeDeath);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Campaign")
		void OnShardPickup();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Campaign")
		void OnDFragPickup();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Campaign|Codex")
		void OnAddToCodex();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnLevelExit();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Settings")
		void AdjustSoundClassVolume(USoundMix* SoundMixInUse, USoundClass* SoundClassInUse, float NewValue, bool bApplyToChildren);
};
