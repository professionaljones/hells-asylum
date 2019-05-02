// Fill out your copyright notice in the Description page of Project Settings.


#include "AsylumGameModeBase.h"

AAsylumGameModeBase::AAsylumGameModeBase()
{
	if (CurrentGameType != MGT_Campaign || CurrentGameType != MGT_UserInterface)
	{
		bIsMissionMode = true;
	}
	else
	{
		bIsMissionMode = false;
	}
}