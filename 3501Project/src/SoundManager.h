#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_
//
//
//
#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

enum  SoundIndex{
			BACKGROUND, 
			SHOOTINGSOUND,
			COLLISIONSOUND

};


namespace AsteroidGame{
	class AsteroidGame; //Forward Declaration

	class SoundManager{
		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		AsteroidGame* iApplication;

		//
		//Public Methods
	public:
		SoundManager(AsteroidGame* aApplication);
		int init();
		int closeAllSoundPlay();
		void audioPlay(int);
		bool isSoundPlaying(int);
		//
		//Private Methods
	private:
	};
}

#endif//SOUND_MANAGER_H_