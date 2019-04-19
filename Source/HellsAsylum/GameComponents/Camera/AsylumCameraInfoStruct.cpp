// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumCameraInfoStruct.h"

bool FAsylumCameraInfo::Equals(const FAsylumCameraInfo & Other) const
{
	FAsylumCameraInfo delta;
	//This will modify the FOV based on the info in the camera modifier
	delta.FOV = FOV - Other.FOV;
	//This will modify the Spring Arm Length based on the info in the camera modifier
	delta.SpringArmLength = SpringArmLength - Other.SpringArmLength;
	delta.NewSpringArmLocation = NewSpringArmLocation + Other.NewSpringArmLocation;
	delta.DepthOfFieldFocalDistance = DepthOfFieldFocalDistance - Other.DepthOfFieldFocalDistance;
	delta.DepthOfFieldFocalRegion = DepthOfFieldFocalRegion - Other.DepthOfFieldFocalRegion;
	delta.DepthOfFieldNearTransitionRegion = DepthOfFieldNearTransitionRegion - Other.DepthOfFieldNearTransitionRegion;
	delta.DepthOfFieldFarTransitionRegion = DepthOfFieldFarTransitionRegion - Other.DepthOfFieldFarTransitionRegion;
	delta.DepthOfFieldNearBlurSize = DepthOfFieldNearBlurSize - Other.DepthOfFieldNearBlurSize;
	delta.DepthOfFieldFarBlurSize = DepthOfFieldFarBlurSize - Other.DepthOfFieldFarBlurSize;
	return delta.IsZero();
}

bool FAsylumCameraInfo::IsZero() const
{
	return FMath::Abs(FOV) < SMALL_NUMBER && FMath::Abs(SpringArmLength) < SMALL_NUMBER &&
		FMath::Abs(DepthOfFieldFocalDistance) < SMALL_NUMBER && FMath::Abs(DepthOfFieldFocalRegion) < SMALL_NUMBER &&
		FMath::Abs(DepthOfFieldNearTransitionRegion) < SMALL_NUMBER &&
		FMath::Abs(DepthOfFieldFarTransitionRegion) < SMALL_NUMBER &&
		FMath::Abs(DepthOfFieldNearBlurSize) < SMALL_NUMBER && FMath::Abs(DepthOfFieldFarBlurSize) < SMALL_NUMBER;
}
