// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	/**
 * Get the array of points to patrol
 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector IndexKey;

	/**
	* Get the next point to patrol
	*/
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector WaypointKey;
	
};
