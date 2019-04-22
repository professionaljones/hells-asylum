// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsylumHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAsylumHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void ShowEndScreen_Campaign();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void ShowEndScreen_Mission();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void ShowPlayerHUD(bool bShowHUD);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnMissionStart();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnMusicPlayer_PlayOneTrack(int32 TrackDesiredAtIndex);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnMusicPlayer_RestoreOriginalSettings();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnMusicPlayer_RepeatOneTrack(int32 TrackDesiredAtIndex);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void ShowMessageToPlayer();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnUpdateMissionPanel();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnUpdateRPC_Mission(float NewPlayerScore);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnCampaignStart();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void OnMainMenuStart();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void MissionLevelFinish();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void MissionLevelCompleted();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void MissionLevelThirdPlaceEnd();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void MissionLevelSecondPlaceEnd();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|UI")
		void MissionLevelFirstPlaceEnd();


};
