// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumCameraModifier.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "GameComponents/AsylumSpringArmComponent.h"

UAsylumCameraModifier::UAsylumCameraModifier(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) : Super(ObjectInitializer),
CurrentModifiers(FAsylumCameraInfo()),
TargetModifiers(FAsylumCameraInfo())
{
}

bool UAsylumCameraModifier::ProcessViewRotation(AActor * ViewTarget, float DeltaTime, FRotator & OutViewRotation, FRotator & OutDeltaRot)
{
	if (!IsValid(ViewTarget))
	{
		return false;
	}

	APawn* pawn = Cast<APawn>(ViewTarget);

	if (!IsValid(pawn))
	{
		return false;
	}

	APlayerController* playerController = Cast<APlayerController>(pawn->Controller);

	if (!IsValid(playerController))
	{
		return false;
	}

	if (!playerController->RotationInput.IsNearlyZero(THRESH_QUAT_NORMALIZED))
	{
		// Reset cooldown.
		CooldownRemaining = CooldownAfterPlayerInput;
		return false;
	}

	if (CooldownRemaining > 0)
	{
		// Tick cooldown.
		CooldownRemaining -= DeltaTime;
		return false;
	}

	return false;
}

FAsylumCameraInfo UAsylumCameraModifier::GetCurrentModifiers() const
{
	return CurrentModifiers;
}

FAsylumCameraInfo UAsylumCameraModifier::GetTargetModifiers() const
{
	return TargetModifiers;
}

void UAsylumCameraModifier::AppyCameraTransition(const FAsylumCameraInfo CameraInfo, const float TransitionTime, FMinimalViewInfo & InOutPOV, const float DeltaTime)
{
	if (!TargetModifiers.Equals(CameraInfo))
	{
		CurrentModifiers = TargetModifiers;
		TargetModifiers = CameraInfo;

		if (RemainingTransitionTime > 0.0f)
		{
			// New transition started before old was finished. Play transition backwards without flipping.
			RemainingTransitionTime = TotalTransitionTime - RemainingTransitionTime;
		}
	}

	if (CurrentModifiers.Equals(TargetModifiers))
	{
		// No changes.
		ApplyCameraInfo(CurrentModifiers, 1.0f, InOutPOV);
		return;
	}

	// Three cases:
	// 1. CurrentModifiers is zero, TargetModifiers is not zero -> Apply new modifiers.
	// 2. CurrentModifiers is not zero, TargetModifiers is zero -> Stop applying modifiers.
	// 3. CurrentModifiers is not zero, TargetModifiers is not zero -> Need transition from current modifiers to new modifiers.
	// TODO(np): Handle Case 3: Need transition from current modifiers to new modifiers.

	// Apply modifiers.
	float applicationFactor = 0.0f;
	FAsylumCameraInfo modifiersToApply;

	if (!TargetModifiers.IsZero())
	{
		// Case 1: Apply new modifiers.
		modifiersToApply = TargetModifiers;

		if (RemainingTransitionTime <= 0.0f)
		{
			// Start transition timer.
			TotalTransitionTime = TransitionTime;
			RemainingTransitionTime = TotalTransitionTime;
		}
		else
		{
			// Tick transition timer.
			RemainingTransitionTime -= DeltaTime;

			if (RemainingTransitionTime <= 0.0f)
			{
				// Transition finished.
				CurrentModifiers = TargetModifiers;
				applicationFactor = 1.0f;
			}
			else
			{
				applicationFactor = 1 - (RemainingTransitionTime / TotalTransitionTime);
			}
		}
	}
	else
	{
		// Case 2: Stop applying modifiers.
		modifiersToApply = CurrentModifiers;

		if (RemainingTransitionTime <= 0.0f)
		{
			// Restart transition timer.
			RemainingTransitionTime = TotalTransitionTime;
			applicationFactor = 1.0f;
		}
		else
		{
			// Tick transition timer.
			RemainingTransitionTime -= DeltaTime;

			if (RemainingTransitionTime <= 0.0f)
			{
				// Transition finished.
				CurrentModifiers = TargetModifiers;
				applicationFactor = 0.0f;
			}
			else
			{
				// This could as well be read as 1 - (1 - (RemainingTransitionTime / TotalTransitionTime)).
				// We want to gradually decrease the influence of the previous modifiers.
				applicationFactor = RemainingTransitionTime / TotalTransitionTime;
			}
		}
	}

	// Apply modifiers.
	ApplyCameraInfo(modifiersToApply, applicationFactor, InOutPOV);
}

bool UAsylumCameraModifier::PlayerHasRecentlyChangedCamera() const
{
	return CooldownRemaining > 0;
}

void UAsylumCameraModifier::ApplyCameraInfo(const FAsylumCameraInfo & CameraInfo, const float Factor, FMinimalViewInfo & InOutPOV) const
{
	float appliedFOV = 0.0f;
	AActor* viewTarget = GetViewTarget();
	// Get player character.
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!IsValid(viewTarget))
	{
		return;
	}

	TArray<USceneComponent*> children;
	viewTarget->GetRootComponent()->GetChildrenComponents(true, children);

	// Apply FOV.
	if (PlayerCharacter->bIsCrouchButtonDown)
	{
		appliedFOV = CameraInfo.FOV_Crouching * Factor;
		InOutPOV.FOV = InOutPOV.FOV + appliedFOV;
	}
	else
	{
		appliedFOV = CameraInfo.FOV * Factor;
		InOutPOV.FOV = InOutPOV.FOV + appliedFOV;
	}


	// Apply spring arm length.
	for (int index = 0; index < children.Num(); ++index)
	{
		UAsylumSpringArmComponent* springArmComponent = Cast<UAsylumSpringArmComponent>(children[index]);

		if (IsValid(springArmComponent))
		{
			springArmComponent->TargetArmLengthModifier += CameraInfo.SpringArmLength * Factor;
			break;
		}
	}

	// Apply depth of field.
	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldFocalDistance))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
		InOutPOV.PostProcessSettings.DepthOfFieldFocalDistance += CameraInfo.DepthOfFieldFocalDistance * Factor;
	}

	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldFocalRegion))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldFocalRegion = true;
		InOutPOV.PostProcessSettings.DepthOfFieldFocalRegion += CameraInfo.DepthOfFieldFocalRegion * Factor;
	}

	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldNearTransitionRegion))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldNearTransitionRegion = true;
		InOutPOV.PostProcessSettings.DepthOfFieldNearTransitionRegion += CameraInfo.DepthOfFieldNearTransitionRegion * Factor;
	}

	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldFarTransitionRegion))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldFarTransitionRegion = true;
		InOutPOV.PostProcessSettings.DepthOfFieldFarTransitionRegion += CameraInfo.DepthOfFieldFarTransitionRegion * Factor;
	}

	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldNearBlurSize))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldNearBlurSize = true;
		InOutPOV.PostProcessSettings.DepthOfFieldNearBlurSize += CameraInfo.DepthOfFieldNearBlurSize * Factor;
	}

	if (!FMath::IsNearlyZero(CameraInfo.DepthOfFieldFarBlurSize))
	{
		InOutPOV.PostProcessSettings.bOverride_DepthOfFieldFarBlurSize = true;
		InOutPOV.PostProcessSettings.DepthOfFieldFarBlurSize += CameraInfo.DepthOfFieldFarBlurSize * Factor;
	}
}
