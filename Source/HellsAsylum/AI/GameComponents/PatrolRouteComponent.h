// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLSASYLUM_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPatrolRouteComponent();


public:
	TArray<AActor*> GetPatrolPoints() const;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;
};
