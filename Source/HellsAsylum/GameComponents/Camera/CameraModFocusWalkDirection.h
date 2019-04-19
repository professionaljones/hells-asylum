// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameComponents/Camera/AsylumCameraModifier.h"
#include "CameraModFocusWalkDirection.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UCameraModFocusWalkDirection : public UAsylumCameraModifier
{
	GENERATED_BODY()

public:
	UCameraModFocusWalkDirection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual bool ModifyCamera(float DeltaTime, struct FMinimalViewInfo& InOutPOV) override;
	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;

private:
	/** Rate at which the camera should follow the turning character, in degrees per second. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float RotationSpeed;

	/** Minimum time between two changes in direction of automatic camera rotation, in seconds. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float DirectionChangeCooldown;

	/** Whether to always rotate the camera to focus walk direction, or only while the player is providing movement input. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		bool RotateOnlyWhileCharacterIsMoving;


	float PreviousYawDeltaSign;
	float DirectionChangeCooldownRemaining;
};
