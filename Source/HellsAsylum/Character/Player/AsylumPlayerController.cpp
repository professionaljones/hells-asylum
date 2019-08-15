// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumPlayerController.h"

AAsylumPlayerController::AAsylumPlayerController()
{

}

void AAsylumPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TeamId = FGenericTeamId(17);
}

FGenericTeamId AAsylumPlayerController::GetGenericTeamId() const
{
	return TeamId;
}
