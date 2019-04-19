// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsylumCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAsylumCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverHealth(float RecoverAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverShield(float RecoverAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnWeaponPickup(TSubclassOf<AAsylumWeapon> WeaponToAdd, int KeyToOccupy);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnCharacterDeath(bool bIsDead);
};
