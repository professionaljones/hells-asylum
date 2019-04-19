// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameComponents/Camera/AsylumCameraModifier.h"
#include "CameraModFocusOnTarget.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UCameraModFocusOnTarget : public UAsylumCameraModifier
{
	GENERATED_BODY()
	
public:
	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation,
		FRotator& OutDeltaRot) override;

	/** Target actor that was selected at the time of the previous camera update. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		AActor* LastTarget;

	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		AActor * currentTarget;

private:
	/** Rate at which the camera should move while not snapping to a target, in degrees per second. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float RotationSpeed;

	/** Rate at which the camera should snap to the target, in degrees per second. */
	UPROPERTY(Category = Custom, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float SnapSpeed;



	/** Desired rotation for focusing the target actor. */
	FRotator DesiredRotation;
};
