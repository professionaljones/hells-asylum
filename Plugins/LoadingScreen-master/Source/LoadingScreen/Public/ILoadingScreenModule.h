// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "MoviePlayer.h"

/**
 * The public interface to this module
 */
class ILoadingScreenModule : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ILoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked< ILoadingScreenModule >("LoadingScreen");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "LoadingScreen" );
	}
};

class FNullMovieStreamer : public IMovieStreamer
{
public:
	FNullMovieStreamer()
	{
		MovieViewport = MakeShareable(new FMovieViewport());
	};
	virtual ~FNullMovieStreamer() {};

	virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) override { return true; };
	virtual void ForceCompletion() override { };
	virtual bool Tick(float DeltaTime) override { return false; };
	virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override { return MovieViewport; };
	virtual float GetAspectRatio() const override { return 0.f; };
	virtual void Cleanup() override { };

	virtual FString GetMovieName() override { return FString(); };
	virtual bool IsLastMovieInPlaylist() override { return false; };

	FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;
	virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override { return OnCurrentMovieClipFinishedDelegate; }

private:
	TSharedPtr<FMovieViewport> MovieViewport;
	
};

