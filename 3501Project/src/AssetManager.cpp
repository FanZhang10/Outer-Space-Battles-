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
		iSkybox = createSkybox();
		//Max Note: Magic number above. Do we just want shield to have a default radius value?
	}

	Ogre::SceneNode* AssetManager::createAsteroid(float aRadius) {
		return iResourceFactory->createAsteroidModel(iApplication->getSceneManager(), aRadius);
	}

	Ogre::SceneNode* AssetManager::createSkybox() {
		return iResourceFactory->createSkyboxModel(iApplication->getSceneManager());
	}

	Ogre::SceneNode* AssetManager::createBoundingBox(Ogre::Vector3 aDimensions) {
		return iResourceFactory->createBoundingBoxModel(iApplication->getSceneManager(), aDimensions);
	}

	Ogre::SceneNode* AssetManager::createProjectile(long counter, int type) {
		return iResourceFactory->createProjectileModel(iApplication->getSceneManager(), counter, type);
	}
}