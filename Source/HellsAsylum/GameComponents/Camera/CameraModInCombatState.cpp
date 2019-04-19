// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "CameraModInCombatState.h"
#include "Camera/CameraTypes.h"
#include "Character/Player/AsylumPlayerCharacter.h"
#include "Character/Player/AsylumPlayerController.h"
#include "Character/Interfaces/CombatActorInterface.h"

bool UCameraModInCombatState::ModifyCamera(float DeltaTime, FMinimalViewInfo & InOutPOV)
{
	Super::ModifyCamera(DeltaTime, InOutPOV);

	// Get player character.
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter->GetClass()->ImplementsInterface(UCombatActorInterface::StaticClass()))
	{

		
		if (PlayerCharacter->bIsInCombat)
		{
			if (!PlayerCharacter->bIsCrouchButtonDown)
			{
				// Apply modifier.
				AppyCameraTransition(PlayerCharacter->IsInCombat() ? Modifiers : FAsylumCameraInfo(), TransitionTime, InOutPOV,
					DeltaTime);

				return true;
			}
			else
			{
				// Apply modifier.
				AppyCameraTransition(PlayerCharacter->IsInCombat() ? Modifiers : FAsylumCameraInfo(), TransitionTime, InOutPOV,
					DeltaTime);
				return true;
			}

		}
		if (!PlayerCharacter->bIsInCombat)
		{
			// Apply modifier.
			AppyCameraTransition(PlayerCharacter->IsInCombat() ? Modifiers : FAsylumCameraInfo(), TransitionTime, InOutPOV,
				DeltaTime);
			return false;
		}

	}
	else
	{
		return false;
	}

	return false;
}

