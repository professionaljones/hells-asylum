// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumCharacterAI.h"

AAsylumCharacterAI::AAsylumCharacterAI()
{
	EnemyStatsComponent = CreateDefaultSubobject<UAsylumStatsComponent>(TEXT("EnemyStatsComponent"));
}