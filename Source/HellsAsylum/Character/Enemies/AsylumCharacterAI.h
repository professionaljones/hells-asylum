// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "Character/AsylumCharacter.h"
#include "AsylumCharacterAI.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API AAsylumCharacterAI : public AAsylumCharacter
{
	GENERATED_BODY()

		

public:
	// Sets default values for this character's properties
	AAsylumCharacterAI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Player|Stats")
		class UAsylumStatsComponent* EnemyStatsComponent;
	
};
