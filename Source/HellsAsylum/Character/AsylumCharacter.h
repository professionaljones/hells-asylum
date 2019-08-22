// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Interfaces/AsylumCharacterInterface.h"
#include "Interfaces/CombatActorInterface.h"
#include "TimerManager.h"
#include "GameComponents/Character/AsylumStatsComponent.h"
#include "GameComponents/Character/AsylumSuitComponent.h"
#include "GameFramework/Character.h"
#include "AsylumCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDataUpdateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDeathDelegate);

UCLASS()
class HELLSASYLUM_API AAsylumCharacter : public ACharacter, public IAsylumCharacterInterface, public ICombatActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAsylumCharacter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, EditAnywhere, BlueprintReadWrite, Category = "Character")
		FCharacterDataUpdateDelegate UpdateCharacterData;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, EditAnywhere, BlueprintReadWrite, Category = "Character")
		FCharacterDeathDelegate CharacterDeathEvent;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Health Percentage", Keywords = "Health"), Category = "Character|Stats")
		float GetHealthPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Shield Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetShieldPercentage();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Aragon Percentage", Keywords = "Shield"), Category = "Character|Stats")
		float GetAragonPercentage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
		bool bIsRunning = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Movement")
		float CharacterRunSpeed = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Movement")
		float CharacterWalkSpeed = 600.0f;

	UFUNCTION(BlueprintCallable, Category = "Character|Weapons")
		virtual void EquipWeapon(AAsylumWeapon* NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Character|Weapons")
		virtual	void HolsterWeapon();

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
		virtual void CharacterSprint();

	bool bIsSprintingToggle = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintCallable, Category = Camera)
	virtual bool IsInCombat() const override;

	virtual bool IsSelectingTarget() const override;
	virtual AActor* GetCurrentTarget() const override;
	virtual FVector2D GetCurrentTargetSelectionInput() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Weapon")
		class AAsylumWeapon* CurrentEquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
		float fMaxLockOnDistance = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
		float fLockOnRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
		bool bIsInCombat = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
		TArray<AActor*> LockOnActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Weapon")
		TArray<TEnumAsByte<EObjectTypeQuery>> TValidLockOnObjects;

	/** Follow camera */
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Character|Stats")
		class UAsylumStatsComponent* CharacterStatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Character|Stats")
		class UAsylumSuitComponent* GoetheSuitComponent;

};
