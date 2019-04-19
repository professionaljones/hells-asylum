// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameComponents/Camera/AsylumCameraModifier.h"
#include "Engine/EngineTypes.h"
#include "CameraModKeepAheadLineOfSight.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UCameraModKeepAheadLineOfSight : public UAsylumCameraModifier
{
	GENERATED_BODY()

public:
	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation,
		FRotator& OutDeltaRot) override;

	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;

	/** How far away from the current camera angle we should look for potential obstacles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float MaximumAngleInRadians;

	/** How precisely we should preemptively look for obstacles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float StepSizeInRadians;

	/** Rate at which the camera should follow the turning character, in radians per second. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float RotationSpeed;

	/** Collision channel of the query probe for verifying line of sight between camera and view target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		TEnumAsByte<ECollisionChannel> LineOfSightProbeChannel;

private:
	/** Checks whether To can be seen from From, with respect to ProbeSize and ProbeChannel. */
	bool IsInLineOfSight(const FVector& From, const FVector& To) const;

	/** Rotates InOutViewLocation and InOutViewRotation around TargetLocation by AngleInRadians. */
	void RotateAroundLocation(const FVector& TargetLocation, FVector& InOutViewLocation, FRotator& InOutViewRotation,
		const float AngleInRadians);
};
