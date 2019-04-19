// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumGameStateBase.h"

void AAsylumGameStateBase::SetLevelScores(float LVMinScore, float TPScore, float SPScore, float FPScore)
{
	CurrentMissionLevelData.LevelMinimumScore = LVMinScore;
	CurrentMissionLevelData.ThirdPlaceMinimumScore = TPScore;
	CurrentMissionLevelData.SecondPlaceMinimumScore = SPScore;
	CurrentMissionLevelData.FirstPlaceMinimumScore = FPScore;
}
