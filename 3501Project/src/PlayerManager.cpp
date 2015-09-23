//
// PlayerManager
//


#include "PlayerManager.h"
#include "bin/path_config.h"

namespace AsteroidGame{

	void PlayerManager::init(){
		iPlayer = new Player();
	}

	void PlayerManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard ,OIS::Mouse* aMouse){
		iPlayer->update(aSceneManager,aKeyboard,aMouse);
	}
}