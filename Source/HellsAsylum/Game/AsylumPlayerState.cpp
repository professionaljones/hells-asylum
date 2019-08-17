// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumPlayerState.h"
#include "HellsAsylum.h"

void AAsylumPlayerState::CachePlayerStats()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CachedCharacterStats.bHasShield = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.bHasShield;
		CachedCharacterStats.fCurrentHealth = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fCurrentHealth;
		CachedCharacterStats.fCurrentShield = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fCurrentShield;
		CachedCharacterStats.fMaxHealth = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fMaxHealth;
		CachedCharacterStats.fMaxShield = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fMaxShield;
		CachedCharacterStats.iCurrentCharacterLevel = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.iCurrentCharacterLevel;
		CachedCharacterStats.iMaxCharacterLevel = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.iMaxCharacterLevel;
		CachedCharacterStats.fFireResist = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fFireResist;
		CachedCharacterStats.fIceResist = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fIceResist;
		CachedCharacterStats.fShockResist = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fShockResist;
		CachedCharacterStats.fMovementLoudness = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fMovementLoudness;
		CachedCharacterStats.fMovementMaxRange = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fMovementMaxRange;
		CachedCharacterStats.fCrouchMovementLoudness = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness;
		CachedCharacterStats.fCrouchMovementMaxRange = PlayerCharacter->CharacterStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange;
		CachedPlayerWeaponInventory = PlayerCharacter->PlayerWeaponInventory;
		CachedPlayerItemInventory = PlayerCharacter->ItemInventory;
	}
	
}
