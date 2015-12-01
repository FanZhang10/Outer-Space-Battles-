//
// PlayerManager
//


#include "PlayerManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"


namespace AsteroidGame{

	PlayerManager::PlayerManager(AsteroidGame* aApplication){
		iApplication = aApplication;

		iHealth = 10;
		iMaxHealth = 100;
		iHealthRegen = .1;
	}

	void PlayerManager::init(Ogre::SceneNode* aCameraNode, Ogre::SceneNode* aCameraNode_2){
		iPlayer = new Player();
		Ogre::SceneNode* lNewPlayerNode = iApplication->getAssetManager()->getPlayerChassis();
		iPlayer->setChassisNode(lNewPlayerNode);

		iShieldNode = iApplication->getAssetManager()->getPlayerShield();

		iCameraNode = aCameraNode;
		iCameraNode_2 = aCameraNode_2;
	}




	void PlayerManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard ,OIS::Mouse* aMouse){

		iPlayer->updateOrientation(aKeyboard, aMouse);
		iPlayer->updatePosition(aKeyboard, aMouse);//to be replaced by //Movement
		

		updateHealth();

		updateCamera();

		iShieldNode->setPosition(iPlayer->getChassisNode()->getPosition());
		iShieldNode->setOrientation(iPlayer->getChassisNode()->getOrientation());
	}


	void PlayerManager::setSkybox(Ogre::SceneNode* aSkybox){
		iSkybox = aSkybox;
	}


	void PlayerManager::updateHealth(){
		iHealth += iHealthRegen;
		if(iHealth > iMaxHealth){
			iHealth = iMaxHealth;
		}
		
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("ShinyBlueMaterial");
		material->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("health",iHealth);
		material->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("maxhealth",iMaxHealth);
	}



	void PlayerManager::updateCamera(){

		Ogre::SceneNode* lPlayerNode = iPlayer->getChassisNode();

		iCameraNode->setPosition(lPlayerNode->getPosition());
		iCameraNode->setOrientation(lPlayerNode->getOrientation());
		iCameraNode->translate(-5-(iPlayer->getSpeed()),1,0,Ogre::Node::TS_LOCAL);
		iCameraNode->roll(Ogre::Degree(15));

		iCameraNode_2->setPosition(lPlayerNode->getPosition() - Ogre::Vector3(0.0, 0.0, 25.0));
		iSkybox->setPosition(iCameraNode->getPosition());

		((Ogre::Camera*) iCameraNode_2->getAttachedObject("MyCamera_2"))->lookAt(lPlayerNode->getPosition());
	}

}