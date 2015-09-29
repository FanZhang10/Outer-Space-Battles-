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

	void AssetManager::createAsteroidField(Ogre::SceneManager* aSceneManager, int aNumAsteroids, Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds, int aStartingSize){
		for(int i = 0; i < aNumAsteroids; i++){
			Ogre::SceneNode* lSceneNode;
			double aRadius = (5.0 - 2.0) * ( (double)rand() / (double)RAND_MAX ) + 2.0;
			lSceneNode = iResourceFactory->createAsteroidModel(aSceneManager, aRadius);
			lSceneNode->setPosition(createVector3InRange(aPositiveBounds, aNegativeBounds));
		}
	}

	Ogre::Vector3 AssetManager::createVector3InRange(Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds){
		Ogre::Vector3 r = Ogre::Vector3((aPositiveBounds.x - aNegativeBounds.x) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.x,
										(aPositiveBounds.y - aNegativeBounds.y) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.y,
										(aPositiveBounds.z - aNegativeBounds.z) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.z);
		return r;
	}

}