//
// AssetManager
//


#include "AssetManager.h"
#include "bin/path_config.h"
#include "OgreApplication.h"

namespace AsteroidGame{

	AssetManager::AssetManager(OgreApplication* aApplication){
		iApplication = aApplication;
	}

	void AssetManager::init(Ogre::SceneManager* aSceneManager){
		iSceneManager = aSceneManager;
	}

	Ogre::SceneNode* AssetManager::CreatePlayerChassis(){
		return createPlayerModel(iSceneManager);
	}

}