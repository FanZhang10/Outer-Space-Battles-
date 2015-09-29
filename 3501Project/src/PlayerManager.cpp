//
// PlayerManager
//


#include "PlayerManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"


namespace AsteroidGame{

	PlayerManager::PlayerManager(AsteroidGame* aApplication){
		iApplication = aApplication;
	}

	void PlayerManager::init(Ogre::SceneNode* aCameraNode){
		iPlayer = new Player();
		Ogre::SceneNode* lNewPlayerNode = iApplication->getAssetManager()->getPlayerChassis();
		iPlayer->setChassisNode(lNewPlayerNode);

		iShieldNode = iApplication->getAssetManager()->getPlayerShield();

		iCameraNode = aCameraNode;
	}




	void PlayerManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard ,OIS::Mouse* aMouse){

		iPlayer->updateOrientation(aKeyboard, aMouse);
		iPlayer->updatePosition(aKeyboard, aMouse);//to be replaced by //Movement
		

		updateCamera();

		iShieldNode->setPosition(iPlayer->getChassisNode()->getPosition());
		iShieldNode->setOrientation(iPlayer->getChassisNode()->getOrientation());
	}




	void PlayerManager::updateCamera(){

		Ogre::SceneNode* lPlayerNode = iPlayer->getChassisNode();

		iCameraNode->setPosition(lPlayerNode->getPosition());
		iCameraNode->setOrientation(lPlayerNode->getOrientation());
		iCameraNode->translate(-5-(iPlayer->getSpeed()),1,0,Ogre::Node::TS_LOCAL);
		iCameraNode->roll(Ogre::Degree(15));
	}
}