//
// AsteroidManager
//


#include "AsteroidManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{

	AsteroidManager::AsteroidManager(AsteroidGame* aApplication) 
		: iTestBB(Ogre::Vector3(50,50,50)), markedForSplit(nullptr)
	{
		iApplication = aApplication;

		for (int i = 1; i <= 4; i++) {
			iTierRadiusMap[i] = (float)(i);
		}

		//Temporary until we find a place to put BoundingBoxes!
		iTestBB.setNode(iApplication->getAssetManager()->createBoundingBox(iTestBB.getBounds()));
	}

	AsteroidManager::~AsteroidManager() {
		markedForSplit = nullptr;
	}

	void AsteroidManager::update() {
		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			(*itr)->update(this, iApplication->getCollisionManager());
		}

		if (markedForSplit != nullptr) {
				splitAsteroid(markedForSplit);
				markedForSplit = nullptr;
		}
	}

	void AsteroidManager::createAsteroidField() {
		for (int i = 0; i < DEFAULT_ASTEROID_NUM; i++) {
			Asteroid* aPtr = createAsteroid( (i % 4) + 1 );
			iAsteroids.push_back(aPtr);
		}

		printf("Asteroids Created! Size = %d\n", iAsteroids.size());

		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			placeAsteroid(*itr);
		}
		
		printf("Asteroids Placed!\n");
	}

	void AsteroidManager::markAsteroidForSplit(Asteroid* aAsteroid) {
		markedForSplit = aAsteroid;
	}



	//Private Functions

	Asteroid* AsteroidManager::createAsteroid(int aTier) {
		return createAsteroid(aTier, iApplication->generateRandomVector3().normalisedCopy());
	}

	Asteroid* AsteroidManager::createAsteroid(int aTier, Ogre::Vector3 aDirection) {
		if (!isLegitimateTier(aTier)) {
			printf ("Error! Incorrect Asteroid Tier %d passed into AsteroidManager::createAsteroid!\n", aTier);
			return nullptr;
		}

		float radius = iTierRadiusMap[aTier];
		Ogre::SceneNode* asteroidNode = iApplication->getAssetManager()->createAsteroid(radius);
		Asteroid* newAsteroid = new Asteroid(asteroidNode, iApplication->generateRandomVector3().normalisedCopy(), aTier, radius);

		return newAsteroid;
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid) {
		//TODO: Define field bounds somewhere in AsteroidGame and get them during this phase
		Ogre::Vector3 randomLocationInField = iApplication->createVector3InRange(Ogre::Vector3(25.0f,25.0f,25.0f), Ogre::Vector3(-25.0f,-25.0f,-25.0f));
		placeAsteroid(aAsteroid, randomLocationInField);
	}

	void AsteroidManager::placeAsteroid(Asteroid* aAsteroid, Ogre::Vector3 aPosition) {
		aAsteroid->getNode()->setPosition(aPosition);
		printf("Asteroid Placed at:    %f %f %f\n", aAsteroid->getNode()->getPosition().x, aAsteroid->getNode()->getPosition().y, aAsteroid->getNode()->getPosition().z);
	}

	
	void AsteroidManager::splitAsteroid(Asteroid* aAsteroid) {

		std::vector<Asteroid*>::iterator itr = iAsteroids.begin();
		for (; itr != iAsteroids.end(); itr++) {
			if ((*itr) == aAsteroid) {
				break;
			}
		}

		//Found aAsteroid in iAsteroids
		if (itr != iAsteroids.end()) {
			Asteroid* asteroidMatch = (*itr);

			if (asteroidMatch == nullptr) {
				printf ("Error! asteroidMatch %p is null; Cannot complete split! Ignoring operation...\n", aAsteroid);
				return;
			}

			iAsteroids.erase(itr);

			if (asteroidMatch == nullptr) {
				printf ("Error! Erase fucks with the pointer :/ \n", aAsteroid);
				return;
			}

			int newTier = asteroidMatch->getTier() - 1;

			//Only create smaller pieces if split asteroid is big enough
			if (newTier > 0) {
				Ogre::Vector3 newDirection = iApplication->generateRandomVector3();

				Asteroid* splitA = createAsteroid(newTier, newDirection);
				Asteroid* splitB = createAsteroid(newTier, -newDirection);

				placeAsteroid(splitA, asteroidMatch->getNode()->getPosition() + newDirection);
				placeAsteroid(splitB, asteroidMatch->getNode()->getPosition() + newDirection);

				splitA->setSpeed(asteroidMatch->getSpeed() * 2);
				splitB->setSpeed(asteroidMatch->getSpeed() * 2);

				iAsteroids.push_back(splitA);
				iAsteroids.push_back(splitB);
			}

			delete asteroidMatch;
		}
		//Didn't find matching asteroid (shouldn't happen)
		else {
			printf ("Error! Couldn't find Asteroid %p in iAsteroids to split! Ignoring operation...\n", aAsteroid);
			return;
		}
	}


	bool AsteroidManager::isLegitimateTier(int aTier) {
		return (aTier >= 1) && (aTier <= 4);
	}

}