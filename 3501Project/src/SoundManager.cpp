//
// Sound Manager
//


#include "SoundManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

#include"framework/Framework.h"
#define NUMBER_OF_AUDIO		7
#define	BACKGOUND_FILE		"backgroundMusic.wav"
#define	EFFECT_FILE_1		"keyeffectMusic2.wav"
#define	EFFECT_FILE_2		"keyeffectMusic2.wav"
#define	EFFECT_FILE_3		"keyeffectMusic2.wav"
#define	EFFECT_FILE_4		"keyeffectMusic2.wav"
#define	EFFECT_FILE_5		"keyeffectMusic2.wav"
#define	EFFECT_FILE_6		"keyeffectMusic2.wav"

ALuint      uiSource[NUMBER_OF_AUDIO];
ALint       iState[NUMBER_OF_AUDIO];
ALuint      uiBuffer[NUMBER_OF_AUDIO];

namespace AsteroidGame{

	SoundManager::SoundManager(AsteroidGame* aApplication){
		iApplication = aApplication;
	}

	int SoundManager::init()
	{
		// Initialize Framework
		ALFWInit();

		ALFWprintf("PlayStatic Test Application\n");

		if (!ALFWInitOpenAL())
		{
			ALFWprintf("Failed to initialize OpenAL\n");
			ALFWShutdown();
			return 0;
		}

		// Generate an AL Buffer
		alGenBuffers(NUMBER_OF_AUDIO, uiBuffer);

		//////////////////////////////////background
		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(BACKGOUND_FILE), uiBuffer[0]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(BACKGOUND_FILE));
		}

		// Generate a Source to playback the Buffer
		alGenSources(NUMBER_OF_AUDIO, uiSource);

		// Attach Source to Buffer
		alSourcei(uiSource[0], AL_BUFFER, uiBuffer[0]);


		//////////////////////////////////////
		// Generate an AL Buffer - 1

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_1), uiBuffer[1]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_1));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[1], AL_BUFFER, uiBuffer[1]);


		//////////////////////////////////////
		// Generate an AL Buffer - 2

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_2), uiBuffer[2]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_2));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[2], AL_BUFFER, uiBuffer[2]);

		//////////////////////////////////////
		// Generate an AL Buffer - 3

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_3), uiBuffer[3]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_3));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[3], AL_BUFFER, uiBuffer[3]);

		//////////////////////////////////////
		// Generate an AL Buffer - 4

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_4), uiBuffer[4]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_4));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[4], AL_BUFFER, uiBuffer[4]);

		//////////////////////////////////////
		// Generate an AL Buffer - 5

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_5), uiBuffer[5]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_5));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[5], AL_BUFFER, uiBuffer[5]);

		//////////////////////////////////////
		// Generate an AL Buffer - 6

		// Load Wave file into OpenAL Buffer
		if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(EFFECT_FILE_6), uiBuffer[6]))
		{
			ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(EFFECT_FILE_6));
		}

		// Attach Source to Buffer
		alSourcei(uiSource[6], AL_BUFFER, uiBuffer[6]);


		return 0;
	}


	int SoundManager::closeAllSoundPlay() {

		// Clean up by deleting Source(s) and Buffer(s)
		alSourceStop(uiSource[0]);
		alSourceStop(uiSource[1]);
		alSourceStop(uiSource[2]);

		alDeleteSources(3, uiSource);
		alDeleteBuffers(3, uiBuffer);

		ALFWShutdownOpenAL();

		ALFWShutdown();

		return 0;
	}

	void SoundManager::audioPlay(int soundIndex)
	{
		alSourcePlay(uiSource[soundIndex]);

	}

	bool SoundManager::isSoundPlaying(int checkIndex)
	{
		alGetSourcei(uiSource[checkIndex], AL_SOURCE_STATE, &iState[checkIndex]);
		return (iState[checkIndex] == AL_PLAYING);
	}

}