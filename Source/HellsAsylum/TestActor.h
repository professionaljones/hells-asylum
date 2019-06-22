// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameComponents/Character/AsylumStatsComponent.h"
#include "TestActor.generated.h"

UCLASS()
class HELLSASYLUM_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Character|Stats")
		UAsylumStatsComponent* StatsComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
