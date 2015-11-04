//
// AsteroidManager
//


#include "AsteroidManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{

	AsteroidManager::AsteroidManager(AsteroidGame* aApplication) 
		: iTestBB(Ogre::Vector3(50,50,50))
	{
		iApplication = aApplication;

		for (int i = 1; i <= 4; i++) {
			iTierRadiusMap[i] = (double)(i);
		}

		//Temporary until we find a place to put BoundingBoxes!
		iTestBB.setNode(iApplication->getAssetManager()->createBoundingBox(iTestBB.getBounds()));
	}

	AsteroidManager::~AsteroidManager() {
	}

	void AsteroidManager::update() {
		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			(*itr)->update(iApplication->getCollisionManager());
		}
	}

	void AsteroidManager::createAsteroidField() {
		printf("GL_ASTEROID_NUM = %f\n", GL_ASTEROID_NUM);
		for (int i = 0; i < GL_ASTEROID_NUM; i++) {
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

		double radius = iTierRadiusMap[aTier];
		Ogre::SceneNode* asteroidNode = iApplication->getAssetManager()->createAsteroid(radius);
		Asteroid* newAsteroid = new Asteroid(asteroidNode, iApplication->generateRandomVector3().normalisedCopy(), aTier, radius);
		//Asteroid* newAsteroid = new Asteroid(asteroidNode, Ogre::Vector3 (1.0,0.0,0.0), aTier, radius);

		iAsteroids.push_back(newAsteroid);
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid) {
		//TODO: Define field bounds somewhere in AsteroidGame and get them during this phase
		//Ogre::Vector3 randomLocationInField = iApplication->createVector3InRange(Ogre::Vector3(50,50,50), Ogre::Vector3(-50,-50,-50));
		Ogre::Vector3 randomLocationInField (0.0,0.0,0.0);
		placeAsteroid(aAsteroid, randomLocationInField);
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid, Ogre::Vector3 aPosition) {
		aAsteroid->getNode()->setPosition(aPosition);
		printf("Asteroid Placed at:    %f %f %f\n", aAsteroid->getNode()->getPosition().x, aAsteroid->getNode()->getPosition().y, aAsteroid->getNode()->getPosition().z);
	}

	bool AsteroidManager::isLegitimateTier(int aTier) {
		return (aTier >= 1) && (aTier <= 4);
	}

}