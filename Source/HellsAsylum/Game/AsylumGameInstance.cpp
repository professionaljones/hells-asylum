// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumGameInstance.h"

UAsylumGameInstance::UAsylumGameInstance()
{
	ManualSaveArray = { "Save01","Save02","Save03","Save04","Save05","Save06","Save07","Save08","Save09","Save10" };
	AutoSaveArray = { "AutoSave01","AutoSave02","AutoSave03","AutoSave04" };
}

float UAsylumGameInstance::GetSavedCurrentXP()
{
	return SaveDataStruct.SavedCurrentPlayerXP;
}

float UAsylumGameInstance::GetSavedXPLimit()
{
	return SaveDataStruct.SavedPlayerXPLimit;
}

TMap<int32, TSubclassOf<AItemBase>> UAsylumGameInstance::GetSavedItemInventory()
{
	return SavedPlayerItemInventory;
}

TMap<int32, TSubclassOf<AAsylumWeapon>> UAsylumGameInstance::GetSavedWeaponInventory()
{
	return SavedPlayerWeaponInventory;
}

FCharacterStatsData UAsylumGameInstance::GetSavedPlayerStats()
{
	return SavedPlayerCharacterStats;
}

FGoetheSuitStatsData UAsylumGameInstance::GetSavedSuitStats()
{
	return SavedPlayerSuitStats;
}

bool UAsylumGameInstance::GetCurrentSaveStatus()
{
	return bWasSaveLoaded;
}
