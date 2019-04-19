// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "CombatActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UCombatActorInterface : public UInterface
{
	GENERATED_BODY()
};

class HELLSASYLUM_API ICombatActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintSetter, Category = Camera)
		virtual bool IsInCombat() const = 0;

		virtual bool IsSelectingTarget() const = 0;
		virtual AActor* GetCurrentTarget() const = 0;
		virtual FVector2D GetCurrentTargetSelectionInput() const = 0;
};
