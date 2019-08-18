// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/AsylumWeapon.h"
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
		void OnGrantFullHealth();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverFullShield();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverHealth(float RecoverAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverShield(float RecoverAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Player")
		void OnWeaponPickup(TSubclassOf<AAsylumWeapon> WeaponToAdd, int32 KeyToOccupy);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnCharacterDeath(bool bIsDead);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnStaminaDrained();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnStaminaDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnRecoverStamina();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Character")
		void OnPlayerLockOn(bool bIsLockedOn);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|AI")
		void OnMissionMode(bool bIsMissionMode);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponEquip(EWeaponType NewWeaponType);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponFire(EWeaponType CurrentWeaponType);

		UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponHolster();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnAI_Fire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnAI_Reload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Game")
		void OnDifficultyModifier(float GameDifficulty);


};
