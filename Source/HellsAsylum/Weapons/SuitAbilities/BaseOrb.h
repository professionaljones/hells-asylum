// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "HellsAsylum.h"
#include "Character/Enemies/AsylumEnemyInterface.h"
#include "Character/Interfaces/AsylumPlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BaseOrb.generated.h"

UCLASS()
class HELLSASYLUM_API ABaseOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseOrb();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> DespairTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Targets")
		TArray<TEnumAsByte<EObjectTypeQuery>> HarmonyTargets;

	//Should this orb apply damage to enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bIsDespair = false;

	//Should this orb apply damage to enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bShouldDealDamage = false;

	//Should this orb attempt to attach to enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool bShouldAttractEnemies = false;

	//How far ahead should the orb's trace search
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float ForwardVectorMod = 0.0f;

	//How much should the orb's trace deal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		float DamageAmount = 0.0f;

	//How large should the trace radius be?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		float DespairTraceRadius = 0.0f;

	//How much damage should the orb apply per successful trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Damage")
		float DespairDamageRate = 0.0f;

	//How much health should the player recieve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Healing")
		float HealAmount = 0.0f;

	//How much health recovery should the orb apply per successful trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Healing")
		float HarmonyHealRate = 0.0f;

	//How large should the trace radius be?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Healing")
		float HarmonyTraceRadius = 0.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float OrbInitialSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
		float OrbMaxSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<AActor*> HarmonyActorsToIgnore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<AActor*> DespairActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FVector EndLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FHitResult DespairHitResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FHitResult HarmonyHitResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector OrbVelocity = FVector(0.0f, 0.0f, 0.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void SearchForEnemies();

	UFUNCTION(BlueprintCallable, Category = "Heal")
		void SearchForPlayer();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player")

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Orb")
		USceneComponent* OrbRoot;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Orb")
		class UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Orb")
		class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Orb")
		UParticleSystem* DespairDestroyPS;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Orb")
		UParticleSystem* HarmonyDestroyPS;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Orb")
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Orb")
		class UProjectileMovementComponent* ProjMovementComponent;

	FTimerHandle DespairOrbTimer;
	FTimerHandle HarmonyOrbTimer;

	/*FORCEINLINE class UStaticMeshComponent* GetSphereMesh() const { return SphereMesh;  }*/

	/** Returns Mesh subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }

};
