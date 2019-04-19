// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "AsylumCameraInfoStruct.h"
#include "AsylumCameraModifier.generated.h"


UCLASS()
class HELLSASYLUM_API UAsylumCameraModifier : public UCameraModifier
{
	GENERATED_BODY()
public:
	UAsylumCameraModifier(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual bool ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;

	/** Gets the camera modifiers that are currently being applied. */
	FAsylumCameraInfo GetCurrentModifiers() const;

	/** Gets the camera modifiers that we are currently transitioning to. */
	FAsylumCameraInfo GetTargetModifiers() const;


	/** How long to wait after player has changed the camera before automatically changing it again, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CooldownAfterPlayerInput;

protected:
	/**
	 * Applies the specifies camera properties, starting a transition if required.
	 *
	 * @param CameraInfo Camera properties to apply. Will start a transition if the specified properties are different from the previous call. May be zero, in which case we'll just be transitioning back.
	 * @param TransitionTime Time until transition to new camera properties should be finished, in seconds. You may pass zero if the transition started in an earlier frame.
	 * @param InOutPOV Camera point of view being modified.
	 * @param DeltaTime Time since the last application of this modifier, in seconds.
	 */
	void AppyCameraTransition(const FAsylumCameraInfo CameraInfo, const float TransitionTime, struct FMinimalViewInfo& InOutPOV, const float DeltaTime);

	/** Whether the player has recently changed the camera. Check this in order to have their input always have priority over automatic adjustments. */
	bool PlayerHasRecentlyChangedCamera() const;

private:
	void ApplyCameraInfo(const FAsylumCameraInfo& CameraInfo, const float Factor, struct FMinimalViewInfo& InOutPOV) const;

	FAsylumCameraInfo CurrentModifiers;
	FAsylumCameraInfo TargetModifiers;
	float TotalTransitionTime;
	float RemainingTransitionTime;

	/** Time before we automatically adjust the camera again, in seconds. */
	float CooldownRemaining;

};
