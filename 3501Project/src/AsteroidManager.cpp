//
// AsteroidManager
//


#include "AsteroidManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{

	AsteroidManager::AsteroidManager(AsteroidGame* aApplication) {
		iApplication = aApplication;

		for (int i = 1; i <= 4; i++) {
			iTierRadiusMap[i] = (double)(i);
		}
	}

	AsteroidManager::~AsteroidManager() {
	}

	void AsteroidManager::update() {
		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			(*itr)->update();
		}
	}

	void AsteroidManager::createAsteroidField() {
		for (int i = 0; i < DEFAULT_ASTEROID_NUM; i++) {
			createAsteroid( (i % 4) + 1 );
		}

		printf("Asteroids Created! Size = %d\n", iAsteroids.size());

		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			placeAsteroid(*itr);
		}
		
		printf("Asteroids Placed!\n");
	}



	//Private Functions

	void AsteroidManager::createAsteroid(int aTier) {

		if (!isLegitimateTier(aTier)) {
			printf ("Error! Incorrect Asteroid Tier %d passed into AsteroidManager::createAsteroid!\n", aTier);
			return;
		}

		Ogre::SceneNode* asteroidNode = iApplication->getAssetManager()->createAsteroid(iTierRadiusMap[aTier]);
		Asteroid* newAsteroid = new Asteroid(asteroidNode, aTier, iApplication->generateRandomVector3().normalisedCopy());

		iAsteroids.push_back(newAsteroid);
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid) {
		//TODO: Define field bounds somewhere in AsteroidGame and get them during this phase
		Ogre::Vector3 randomLocationInField = iApplication->createVector3InRange(Ogre::Vector3(50,50,50), Ogre::Vector3(-50,-50,-50));
		placeAsteroid(aAsteroid, randomLocationInField);
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid, Ogre::Vector3 aPosition) {
		aAsteroid->getNode()->setPosition(aPosition);
	}

	bool AsteroidManager::isLegitimateTier(int aTier) {
		return (aTier >= 1) && (aTier <= 4);
	}

}