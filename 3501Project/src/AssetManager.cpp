//
// AssetManager
//


#include "AssetManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{

	AssetManager::AssetManager(AsteroidGame* aApplication) :
	iApplication(aApplication)
	{
		iResourceFactory = new ResourceFactory();
	}

	AssetManager::~AssetManager(){
		if (iResourceFactory) {
			delete iResourceFactory;
		}
	}

	void AssetManager::init(Ogre::SceneManager* aSceneManager){
		iSceneManager = aSceneManager;

		iPlayerChassis = iResourceFactory->createPlayerModel(iSceneManager);
		iPlayerShield = iResourceFactory->createShieldModel(iSceneManager, 1.5);
		//Max Note: Magic number above. Do we just want shield to have a default radius value?
	}

	Ogre::SceneNode* AssetManager::createAsteroid(double aRadius) {
		return iResourceFactory->createAsteroidModel(iApplication->getSceneManager(), aRadius);
	}
}