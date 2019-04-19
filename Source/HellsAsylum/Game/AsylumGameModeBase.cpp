// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumGameModeBase.h"

AAsylumGameModeBase::AAsylumGameModeBase()
{
	if (CurrentGameType != GT_Campaign || CurrentGameType != GT_UserInterface)
	{
		bIsMissionMode = true;
	}
	else
	{
		bIsMissionMode = false;
	}
}