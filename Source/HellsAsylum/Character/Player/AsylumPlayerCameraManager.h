// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "AsylumPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	/** Radius of the query probe for verifying line of sight between camera and view target (in cm). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float LineOfSightProbeSize;

	/** Collision channel of the query probe for verifying line of sight between camera and view target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		TEnumAsByte<ECollisionChannel> LineOfSightProbeChannel;

protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
