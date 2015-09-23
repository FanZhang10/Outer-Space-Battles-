//
// PlayerManager
//


#include "PlayerManager.h"
#include "bin/path_config.h"
#include "OgreApplication.h"


namespace AsteroidGame{

	PlayerManager::PlayerManager(OgreApplication* aApplication){
		iApplication = aApplication;
	}

	void PlayerManager::init(Ogre::SceneNode* aCameraNode){
		iPlayer = new Player();
		Ogre::SceneNode* lNewPlayerNode = iApplication->getAssetManager()->CreatePlayerChassis();
		iPlayer->setChassisNode(lNewPlayerNode);

		iCameraNode = aCameraNode;
	}




	void PlayerManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard ,OIS::Mouse* aMouse){

		iPlayer->updateOrientation(aKeyboard, aMouse);
		iPlayer->updatePosition(aKeyboard, aMouse);//to be replaced by //Movement


		updateCamera();
	}




	void PlayerManager::updateCamera(){

		Ogre::SceneNode* lPlayerNode = iPlayer->getChassisNode();

		iCameraNode->setPosition(lPlayerNode->getPosition());
		iCameraNode->setOrientation(lPlayerNode->getOrientation());
		iCameraNode->translate(-5-(iPlayer->getSpeed()),1,0,Ogre::Node::TS_LOCAL);
		iCameraNode->roll(Ogre::Degree(15));
	}
}