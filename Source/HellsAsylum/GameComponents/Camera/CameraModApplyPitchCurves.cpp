// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "CameraModApplyPitchCurves.h"
#include "Character/Player/AsylumPlayerCameraManager.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Camera/CameraTypes.h"

bool UCameraModApplyPitchCurves::ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV)
{
	Super::ModifyCamera(DeltaTime, InOutPOV);

	AAsylumPlayerCameraManager* CameraManager = Cast<AAsylumPlayerCameraManager>(CameraOwner);

	if (!IsValid(CameraManager))
	{
		return false;
		GLog->Log("Not using correct Camera Manager");
	}

	// Get camera location and rotation.
	const FVector cameraLocation = InOutPOV.Location;
	const FRotator cameraRotation = InOutPOV.Rotation;

	// Apply curves.
	const float pitchToDistance = IsValid(PitchToDistanceCurve) ? PitchToDistanceCurve->GetFloatValue(cameraRotation.Pitch) : 0.0f;
	const float pitchToFov = IsValid(PitchToFOVCurve) ? PitchToFOVCurve->GetFloatValue(cameraRotation.Pitch) : 0.0f;

	// Drive camera away based on evaluated curve.
	const FVector desiredLocation =
		cameraLocation - cameraRotation.RotateVector(FVector::ForwardVector) * pitchToDistance;

	FVector newLocation;
	FCollisionQueryParams queryParams(SCENE_QUERY_STAT(SpringArm), false, GetViewTarget());
	FHitResult result;
	GetWorld()->SweepSingleByChannel(result, GetViewTarget()->GetActorLocation(), desiredLocation, FQuat::Identity,
		CameraManager->LineOfSightProbeChannel,
		FCollisionShape::MakeSphere(CameraManager->LineOfSightProbeSize), queryParams);
	newLocation = result.bBlockingHit ? result.Location : desiredLocation;

	InOutPOV.Location = newLocation;
	InOutPOV.FOV += pitchToFov;
	return true;
}