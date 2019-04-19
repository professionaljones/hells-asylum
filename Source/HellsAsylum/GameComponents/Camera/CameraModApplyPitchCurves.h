// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameComponents/Camera/AsylumCameraModifier.h"
#include "Curves/CurveFloat.h"
#include "Camera/CameraModifier.h"
#include "CameraModApplyPitchCurves.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UCameraModApplyPitchCurves : public UAsylumCameraModifier
{
	GENERATED_BODY()

public:
	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;

private:
	// Curve to convert changes in pitch to changes in camera distance.
	UPROPERTY(Category = Custom, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* PitchToDistanceCurve;

	// Curve to convert changes in pitch to changes in field of view.
	UPROPERTY(Category = Custom, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* PitchToFOVCurve;
};
