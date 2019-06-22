// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatsComponent = CreateDefaultSubobject<UAsylumStatsComponent>(TEXT("StatsComponent"));

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATestActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageTaken = DamageAmount;

	if (StatsComponent->CharacterStatsDataStruct.fCurrentShield >= StatsComponent->CharacterStatsDataStruct.fMaxShield)
	{
		StatsComponent->CharacterStatsDataStruct.fCurrentShield = StatsComponent->CharacterStatsDataStruct.fCurrentShield - DamageTaken;
	}
	else if (StatsComponent->CharacterStatsDataStruct.fCurrentShield <= 0)
	{
		StatsComponent->CharacterStatsDataStruct.fCurrentHealth = StatsComponent->CharacterStatsDataStruct.fCurrentHealth - DamageTaken;
	}

	return DamageTaken;
}

