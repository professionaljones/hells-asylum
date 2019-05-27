// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AsylumWeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UAsylumWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API IAsylumWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnFinishReload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnInfiniteAmmoToggle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnUnlimitedClipsToggle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void SetWeaponOwner();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnStartReload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnGrantFullAmmo();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnHitTarget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnCriticalHit();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnStartFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnFinishFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnEmptyWeaponFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnWeaponAmmoPickup(float AmmoToAdd);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void RecalculateBaseWeaponDamage();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void OnDamageModify();

	/*UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Weapon")
		void RevertDamageChanges();*/

	/*UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category = "Weapon|Stats|Damage")
		float DamageAmountProcessor(float BaseDamage, float DamageMultiplierAmount, float DamageModifierAmount);*/
};
