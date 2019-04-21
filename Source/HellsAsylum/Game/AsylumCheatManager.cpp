// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED


#include "AsylumCheatManager.h"
#include "Character/Player/AsylumPlayerCharacter.h"

void UAsylumCheatManager::EnablePlayerInfiniteAmmo()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerCharacter->CurrentEquippedWeapon))
	{
		PlayerCharacter->CurrentEquippedWeapon->Execute_OnInfiniteAmmoToggle(PlayerCharacter->CurrentEquippedWeapon);
	}

}

void UAsylumCheatManager::EnablePlayerUnlimitedClips()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerCharacter->CurrentEquippedWeapon))
	{
		PlayerCharacter->CurrentEquippedWeapon->Execute_OnUnlimitedClipsToggle(PlayerCharacter->CurrentEquippedWeapon);
	}
}

void UAsylumCheatManager::EnablePlayerGodMode()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter->GetClass()->ImplementsInterface(UAsylumPlayerInterface::StaticClass()))
	{
		PlayerCharacter->Execute_OnGodModeToggle(PlayerCharacter);
	}
}

void UAsylumCheatManager::EnablePlayerSuit()
{
	AAsylumPlayerCharacter* PlayerCharacter = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter->GetClass()->ImplementsInterface(UAsylumPlayerInterface::StaticClass()))
	{
		PlayerCharacter->Execute_OnPlayerSuitEnable(PlayerCharacter);

	}
}
