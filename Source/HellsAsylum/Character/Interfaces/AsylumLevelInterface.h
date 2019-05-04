// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsylumLevelInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAsylumLevelInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumLevelInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnLevelTransition();
};
