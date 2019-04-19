// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "MapNamesBPLibrary.generated.h"

/*
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UMapNamesBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


		UFUNCTION(BlueprintPure, meta = (DisplayName = "GetAllMapNames", Keywords = "GAMNMaps"), Category = "MapNames")
		static FORCEINLINE TArray<FString> GetAllMapNames_p()
	{
		TArray<FString> MapFiles;

		IFileManager::Get().FindFilesRecursive(MapFiles, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

		for (int32 i = 0; i < MapFiles.Num(); i++)
		{
			//replace the whole directory string with only the name of the map

			int32 lastSlashIndex = -1;
			if (MapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureMapName;

				//length - 5 because of the ".umap" suffix
				for (int32 j = lastSlashIndex + 1; j < MapFiles[i].Len() - 5; j++)
				{
					pureMapName.AppendChar(MapFiles[i][j]);
				}

				MapFiles[i] = pureMapName;
			}
		}

		return MapFiles;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAllMapNames", Keywords = "GAMNMaps"), Category = "MapNames")
		static FORCEINLINE TArray<FString> GetAllMapNames()
	{
		TArray<FString> MapFiles;

		IFileManager::Get().FindFilesRecursive(MapFiles, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

		for (int32 i = 0; i < MapFiles.Num(); i++)
		{
			//replace the whole directory string with only the name of the map

			int32 lastSlashIndex = -1;
			if (MapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureMapName;

				//length - 5 because of the ".umap" suffix
				for (int32 j = lastSlashIndex + 1; j < MapFiles[i].Len() - 5; j++)
				{
					pureMapName.AppendChar(MapFiles[i][j]);
				}

				MapFiles[i] = pureMapName;
			}
		}

		return MapFiles;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get All Story Map Names", Keywords = "Get Maps"), Category = "Game Data")
		static FORCEINLINE TArray<FString> GetAllStoryMapNames_p()
	{
		TArray<FString> StoryMapFiles;

		IFileManager::Get().FindFilesRecursive(StoryMapFiles, *FPaths::ProjectContentDir(), TEXT("CM_*.umap"), true, false, false);

		for (int32 i = 0; i < StoryMapFiles.Num(); i++)
		{
			int32 lastSlashIndex = -1;
			if (StoryMapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureStoryMapName;

				for (int32 j = lastSlashIndex + 1; j < StoryMapFiles[i].Len() - 5; j++)
				{
					pureStoryMapName.AppendChar(StoryMapFiles[i][j]);
				}

				StoryMapFiles[i] = pureStoryMapName;
			}
		}

		return StoryMapFiles;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get All Mission Map Names", Keywords = "Get Mission Maps"), Category = "Game Data")
		static FORCEINLINE TArray<FString> GetAllMissionMapNames_p()
	{
		TArray<FString> MissionMapFiles;

		IFileManager::Get().FindFilesRecursive(MissionMapFiles, *FPaths::ProjectContentDir(), TEXT("AM_*.umap"), true, false, false);

		for (int32 i = 0; i < MissionMapFiles.Num(); i++)
		{
			int32 lastSlashIndex = -1;
			if (MissionMapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureMissionMapName;

				for (int32 j = lastSlashIndex + 1; j < MissionMapFiles[i].Len() - 5; j++)
				{
					pureMissionMapName.AppendChar(MissionMapFiles[i][j]);
				}

				MissionMapFiles[i] = pureMissionMapName;
			}
		}

		return MissionMapFiles;
	}
};
