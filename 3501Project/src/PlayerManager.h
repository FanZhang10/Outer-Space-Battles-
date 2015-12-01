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
		AsteroidGame* iApplication;
		Player* iPlayer;
		//
		//Private Variables
	private:
		

		Ogre::SceneNode* iCameraNode;
		Ogre::SceneNode* iCameraNode_2;
		Ogre::SceneNode* iShieldNode;
		Ogre::SceneNode* iSkybox;
		Ogre::SceneNode* iEngine;
		Ogre::SceneNode* iTurbine;

		float iHealth;
		float iMaxHealth;
		float iHealthRegen;
		//
		//Public Methods
	public:
		PlayerManager(AsteroidGame* aApplication);
		void init(Ogre::SceneNode*,Ogre::SceneNode*);
		void update(Ogre::SceneManager* ,OIS::Keyboard* ,OIS::Mouse* );
		void updateCamera();
		void updateHealth();
		void setSkybox(Ogre::SceneNode*);
		void setHealth(float aHealth) { iHealth = aHealth; }

		Player* getPlayer() { return iPlayer; }
		float getCurrentHealth() { return iHealth; }
		//
		//Private Methods
	private:

	};
}

#endif//PLAYER_MANAGER_H_