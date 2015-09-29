//
// AssetManager
//


#include "AssetManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{

	AssetManager::AssetManager(AsteroidGame* aApplication){
		iApplication = aApplication;
	}

	void AssetManager::init(Ogre::SceneManager* aSceneManager){
		iSceneManager = aSceneManager;
	}

	Ogre::SceneNode* AssetManager::CreatePlayerChassis(){
		return createPlayerModel(iSceneManager);
	}

	Ogre::SceneNode* AssetManager::CreatePlayerShield(){
		return createShieldModel(iSceneManager, 1.5);
	 }

}