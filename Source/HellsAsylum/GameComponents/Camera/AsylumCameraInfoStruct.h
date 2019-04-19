// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "AsylumCameraInfoStruct.generated.h"

/** Common camera properties that can be added or overridden for a camera. */
USTRUCT(BlueprintType)
struct FAsylumCameraInfo
{
	GENERATED_USTRUCT_BODY()

		/** The field of view (in degrees) in perspective mode (ignored in Orthographic mode) */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float FOV;

	/** The field of view (in degrees) in perspective mode (ignored in Orthographic mode) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float FOV_Crouching;

	/** Modify the location of the spring arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		FVector NewSpringArmLocation;
	
	/** Distance between the camera and the view target, in cm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float SpringArmLength;

	/** Distance in which the Depth of Field effect should be sharp, in unreal units (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldFocalDistance;

	/** Artificial region where all content is in focus, starting after DepthOfFieldFocalDistance, in unreal units  (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldFocalRegion;

	/** To define the width of the transition region next to the focal region on the near side (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldNearTransitionRegion;

	/** To define the width of the transition region next to the focal region on the near side (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldFarTransitionRegion;

	/** Gaussian only: Maximum size of the Depth of Field blur (in percent of the view width) (note: performance cost scales with size) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldNearBlurSize;

	/** Gaussian only: Maximum size of the Depth of Field blur (in percent of the view width) (note: performance cost scales with size) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DepthOfField)
		float DepthOfFieldFarBlurSize;

	/** Compares both camera property sets for equality. */
	bool Equals(const FAsylumCameraInfo& Other) const;

	/** Whether this property set modifies the camera at all. */
	bool IsZero() const;
};
