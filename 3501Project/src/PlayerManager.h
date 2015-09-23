#ifndef PLAYER_MANAGER_H_
#define PLAYER_MANAGER_H_
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
#include "Player.h"

namespace AsteroidGame{
	class PlayerManager{

		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		Player* iPlayer;

		//
		//Public Methods
	public:
		void init();
		void update(Ogre::SceneManager* ,OIS::Keyboard* ,OIS::Mouse* );

		//
		//Private Methods
	private:

	};
}

#endif//PLAYER_MANAGER_H_