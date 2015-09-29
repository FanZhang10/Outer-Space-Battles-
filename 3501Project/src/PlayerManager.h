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
	class AsteroidGame; //Forward Declaration

	class PlayerManager{

		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		AsteroidGame* iApplication;
		Player* iPlayer;

		Ogre::SceneNode* iCameraNode;
		Ogre::SceneNode* iShieldNode;

		//
		//Public Methods
	public:
		PlayerManager(AsteroidGame* aApplication);
		void init(Ogre::SceneNode*);
		void update(Ogre::SceneManager* ,OIS::Keyboard* ,OIS::Mouse* );
		void updateCamera();
		//
		//Private Methods
	private:

	};
}

#endif//PLAYER_MANAGER_H_