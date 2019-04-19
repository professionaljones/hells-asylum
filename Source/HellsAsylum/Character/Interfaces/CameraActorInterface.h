// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "HellsAsylum.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "CameraActorInterface.generated.h"

class AAsylumCameraModificationVolume;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCameraActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLSASYLUM_API ICameraActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual AAsylumCameraModificationVolume* GetCurrentCameraModificationVolume() const = 0;
	virtual void SetCurrentCameraModificationVolume(AAsylumCameraModificationVolume* CurrentCameraModificationVolume) = 0;
};
