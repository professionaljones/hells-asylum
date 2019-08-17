// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumAIController.h"

AAsylumAIController::AAsylumAIController()
{
	SetGenericTeamId(FGenericTeamId(13));
}

ETeamAttitude::Type AAsylumAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn * OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface * TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			//Actors with same ID# are Friendly
			//Actors with different IDs are currently all hostiles
			if (OtherTeamID == 10)
			{
				return ETeamAttitude::Neutral;
			}
			else if (OtherTeamID == 13)
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}

			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Neutral;
}
