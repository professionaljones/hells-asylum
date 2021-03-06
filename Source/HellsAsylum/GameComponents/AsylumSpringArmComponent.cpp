// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumSpringArmComponent.h"

UAsylumSpringArmComponent::UAsylumSpringArmComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Enable camera controls.
	bUsePawnControlRotation = true;
	BaseSpringArmLocation = GetComponentLocation();

	// Set reasonable default values for camera distance and perspective.
	BaseTargetArmLength = 350.0f;
	SocketOffset = FVector(0.0f, 40.0f, 40.0f);

	// Enable camera lag.
	bEnableCameraLag = true;
	CameraLagSpeed = 5.0f;
	/*bEnableCameraRotationLag = true;
	CameraRotationLagSpeed = 5.0f;*/
}

void UAsylumSpringArmComponent::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime)
{
	TargetArmLength = BaseTargetArmLength + TargetArmLengthModifier;
	TargetArmLocationModifer = BaseSpringArmLocation + TargetArmLocationModifer;
	Super::UpdateDesiredArmLocation(bDoTrace, bDoLocationLag, bDoRotationLag, DeltaTime);
	TargetArmLengthModifier = 0.0f;
}