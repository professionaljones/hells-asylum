// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "AsylumPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AAsylumPlayerController();
	
protected:
	virtual void BeginPlay();

	// Implement The Generic Team Interface 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Perception")
		FGenericTeamId TeamId;

	FGenericTeamId GetGenericTeamId() const;
};
