// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "CameraModFocusWalkDirection.h"
#include "GameFramework/Actor.h"
#include "Character/Interfaces/AsylumPlayerInterface.h"

UCameraModFocusWalkDirection::UCameraModFocusWalkDirection(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	RotationSpeed = 10.0f;
}

bool UCameraModFocusWalkDirection::ModifyCamera(float DeltaTime, FMinimalViewInfo & InOutPOV)
{
	return Super::ModifyCamera(DeltaTime, InOutPOV);
}

bool UCameraModFocusWalkDirection::ProcessViewRotation(AActor * ViewTarget, float DeltaTime, FRotator & OutViewRotation, FRotator & OutDeltaRot)
{
	Super::ProcessViewRotation(ViewTarget, DeltaTime, OutViewRotation, OutDeltaRot);

	// Tick cooldown.
	if (DirectionChangeCooldownRemaining > 0)
	{
		DirectionChangeCooldownRemaining -= DeltaTime;
	}

	IAsylumPlayerInterface* playerCharacter = Cast<IAsylumPlayerInterface>(ViewTarget);

	if (!playerCharacter)
	{
		return false;
		GLog->Log("Nope");
	}

	// Check if we should apply automatic rotation.
	if (RotateOnlyWhileCharacterIsMoving && !playerCharacter->GotMovementInput())
	{
		return false;
	}

	if (PlayerHasRecentlyChangedCamera())
	{
		return false;
	}

	// Get current actor and view rotations.
	const float actorYaw = ViewTarget->GetActorRotation().Yaw;
	const float viewYaw = OutViewRotation.Yaw;

	// Always take the "short route" while rotating.
	float yawDelta = actorYaw - viewYaw;

	while (yawDelta < -180.0f)
	{
		yawDelta += 360.0f;
	}

	while (yawDelta > 180.0f)
	{
		yawDelta -= 360.0f;
	}

	// Check direction of rotation.
	float yawDeltaSign = FMath::Sign(yawDelta);

	if (PreviousYawDeltaSign != yawDeltaSign)
	{
		if (DirectionChangeCooldownRemaining > 0)
		{
			return false;
		}
		else
		{
			PreviousYawDeltaSign = yawDeltaSign;
			DirectionChangeCooldownRemaining = DirectionChangeCooldown;
		}
	}

	// Apply rotation speed.
	float appliedYawDelta = yawDeltaSign * RotationSpeed * DeltaTime;

	// Prevent flipping back and forth for very small deltas.
	if (FMath::Abs(yawDelta) < FMath::Abs(appliedYawDelta))
	{
		PreviousYawDeltaSign = 0.0f;
		DirectionChangeCooldownRemaining = DirectionChangeCooldown;
		appliedYawDelta = yawDelta;
	}

	OutDeltaRot.Yaw += appliedYawDelta;


	return false;
}
