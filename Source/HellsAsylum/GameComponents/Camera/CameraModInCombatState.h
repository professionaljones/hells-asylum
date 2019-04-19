// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameComponents/Camera/AsylumCameraModifier.h"
#include "CameraModInCombatState.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UCameraModInCombatState : public UAsylumCameraModifier
{
	GENERATED_BODY()

public:

	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;

	/** Time until the modifications are fully applied, in seconds. */
	UPROPERTY(Category = CameraModifiers, BlueprintReadWrite, EditAnywhere)
		float TransitionTime;

	/** Value to add to the current properties of the camera of any player in combat. */
	UPROPERTY(Category = CameraModifiers, BlueprintReadWrite, EditAnywhere)
		FAsylumCameraInfo Modifiers;
};
