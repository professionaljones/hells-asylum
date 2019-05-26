// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumPlayerState.h"
#include "HellsAsylum.h"

void AAsylumPlayerState::CachePlayerStats()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CachedCharacterStats.bHasShield = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.bHasShield;
		CachedCharacterStats.fCurrentHealth = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fCurrentHealth;
		CachedCharacterStats.fCurrentShield = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fCurrentShield;
		CachedCharacterStats.fMaxHealth = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fMaxHealth;
		CachedCharacterStats.fMaxShield = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fMaxShield;
		CachedCharacterStats.iCurrentCharacterLevel = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.iCurrentCharacterLevel;
		CachedCharacterStats.iMaxCharacterLevel = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.iMaxCharacterLevel;
		CachedCharacterStats.fFireResist = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fFireResist;
		CachedCharacterStats.fIceResist = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fIceResist;
		CachedCharacterStats.fShockResist = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fShockResist;
		CachedCharacterStats.fMovementLoudness = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fMovementLoudness;
		CachedCharacterStats.fMovementMaxRange = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fMovementMaxRange;
		CachedCharacterStats.fCrouchMovementLoudness = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementLoudness;
		CachedCharacterStats.fCrouchMovementMaxRange = PlayerCharacter->PlayerStatsComponent->CharacterStatsDataStruct.fCrouchMovementMaxRange;
		CachedPlayerWeaponInventory = PlayerCharacter->PlayerWeaponInventory;
		CachedPlayerItemInventory = PlayerCharacter->ItemInventory;
	}
	
}
