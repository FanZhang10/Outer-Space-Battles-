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

	void PlayerManager::init(){
		iPlayer = new Player();
		Ogre::SceneNode* lNewPlayerNode = iApplication->getAssetManager()->CreatePlayerChassis();
		iPlayer->setChassisNode(lNewPlayerNode);
	}

	void PlayerManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard ,OIS::Mouse* aMouse){
		iPlayer->update(aSceneManager,aKeyboard,aMouse);
	}
}