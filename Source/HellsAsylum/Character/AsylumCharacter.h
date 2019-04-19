// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/AsylumCharacterInterface.h"
#include "Interfaces/CombatActorInterface.h"
#include "TimerManager.h"
#include "GameComponents/Character/AsylumStatsComponent.h"
#include "GameFramework/Character.h"
#include "AsylumCharacter.generated.h"

UCLASS()
class HELLSASYLUM_API AAsylumCharacter : public ACharacter, public IAsylumCharacterInterface, public ICombatActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAsylumCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Weapon|")
			TArray<TEnumAsByte<EObjectTypeQuery>> TValidLockOnObjects;

		/** Follow camera */
		UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Camera")
			class UCameraComponent* FollowCamera;

		UFUNCTION(BlueprintCallable, Category = "Weapon")
			void LockOn();

};
