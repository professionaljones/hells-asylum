// Copyright 2019 Eternal Starlight Studios ALL RIGHTS RESERVED

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "AsylumCheatManager.generated.h"


UCLASS()
class HELLSASYLUM_API UAsylumCheatManager : public UCheatManager
{
	GENERATED_BODY()
	

	UFUNCTION(Exec, Category = "Cheats")
		void EnablePlayerInfiniteAmmo();

	UFUNCTION(Exec, Category = "Cheats")
		void EnablePlayerUnlimitedClips();

	UFUNCTION(Exec, Category = "Cheats")
		void EnablePlayerGodMode();

	UFUNCTION(Exec, Category = "Cheats")
		void EnablePlayerSuit();

private:
	bool bEnableInfiniteAmmo = false;
	bool bEnableNoClipsLimit = false;
	bool bEnableGodMode = false;
};
