// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "AsylumDamageType.generated.h"

/**
 * 
 */
UCLASS()
class HELLSASYLUM_API UAsylumDamageType : public UDamageType
{
	GENERATED_BODY()


public:

	UAsylumDamageType();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* PSC;
};
