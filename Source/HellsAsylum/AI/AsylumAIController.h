// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "AsylumAIController.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumAIController : public AAIController
{
	GENERATED_BODY()

public:

	//Constructor
	AAsylumAIController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName AttackerKey = "Attacker";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName CurrentHealthKey = "CurrentHealth";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName CurrentShieldKey = "CurrentShield";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName CurrentPowerKey = "CurrentPowerGauge";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName MaxPowerKey = "MaxPowerGauge";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName CurrentAmmoKey = "CurrentAmmo";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName MaxAmmoKey = "RemainingClips";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName LastLocationKey = "LastSeenLocation";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Keys")
		FName LastHeardKey = "LastHeardLocation";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
		UBehaviorTree* CurrentBehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
		UBlackboardData* CurrentBlackboardData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
		UBlackboardComponent* CurrentBlackboardComponent;

public:
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
