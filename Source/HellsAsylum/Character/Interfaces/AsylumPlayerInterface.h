// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Items/ItemBase.h"
#include "AsylumPlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAsylumPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool GotMovementInput() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerActivate();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerDeathEvent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerSuitEnable();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void PlayerUIUpdate();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerReload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerReloadFinish();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerUseItem(TSubclassOf<AItemBase> ItemInUse);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerConsumeItem(int32 ItemAtIndexToRemove);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerDrawWeapon(bool bIsWeaponActive);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Cheats")
		void OnGodModeToggle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Cheats")
		void OnPlayerRecoverFullStats();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerRecoverFullHealth();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerRecoverFullShield();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnPlayerRecoverFullAragon();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Interact")
		void OnInteractVisible();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Interact")
		void OnInteractNotVisible();
};
