// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumGameInstance.h"

UAsylumGameInstance::UAsylumGameInstance()
{
	ManualSaveArray = { "NOTASAVE","Save01","Save02","Save03","Save04","Save05","Save06","Save07","Save08","Save09","Save10" };
	AutoSaveArray = { "NOTASAVE","AutoSave01","AutoSave02","AutoSave03","AutoSave04" };
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

TMap<int32, class AAsylumWeapon*> UAsylumGameInstance::GetSavedWeaponArray()
{
	return SavedPlayerWeaponArray;
}

FName UAsylumGameInstance::GetCampaignDifficultyName()
{
	switch (SaveDataStruct.SavedGameDifficulty_Campaign)
	{
	case 1:
		return "Easy";
		break;
	case 2:
		return "Normal";
		break;
	case 3:
		return "Hard";
		break;
	case 4:
		return "Extreme";
		break;
	case 5:
		return "Huntress";
		break;
	case 6:
		return "Easy+";
		break;
	case 7:
		return "Normal+";
		break;
	case 8:
		return "Hard+";
		break;
	case 9:
		return "Extreme+";
		break;
	case 10:
		return "Huntress+";
		break;
	default:
		return "No Difficulty";
		UE_LOG(LogTemp,Warning,TEXT("No difficulty has been selected/saved!"));
		break;
	}
}

void UAsylumGameInstance::SetCampaignDiffculty(int32 NewDifficulty)
{
	SaveDataStruct.SavedGameDifficulty_Campaign = NewDifficulty;
	//return SaveDataStruct.SavedGameDifficulty_Campaign;
}

int32 UAsylumGameInstance::GetCampaignDifficulty()
{
	return SaveDataStruct.SavedGameDifficulty_Campaign;
}
