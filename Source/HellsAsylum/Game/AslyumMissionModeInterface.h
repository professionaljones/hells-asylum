// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AslyumMissionModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAslyumMissionModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAslyumMissionModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnMissionEnemyKill(float PointsToAdd);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnMissionEnemyCritKill(float PointsToAdd);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnCalculatePlayerScore();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnMissionFail();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnCritStart(float NewMultiplierAmount, float MultiplierTimeLimit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Mission")
		void OnCritEnd();

};
