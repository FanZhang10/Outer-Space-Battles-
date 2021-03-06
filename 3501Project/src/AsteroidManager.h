#ifndef ASTEROID_MANAGER_H_
#define ASTEROID_MANAGER_H_
//
//
//
#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

#include "Asteroid.h"
#include "BoundingBox.h"

#define DEFAULT_ASTEROID_NUM 25

namespace AsteroidGame{
	class AsteroidGame; //Forward Declaration

	class AsteroidManager{
		//
		//Public Variables
	public:
		AsteroidGame* iApplication;
		
		//Temporary until we find a place to put BoundingBoxes!
		BoundingBox iTestBB;

		//
		//Private Variables
	private:
		std::map<int, float> iTierRadiusMap;
		std::vector<Asteroid*> iAsteroids;

		Asteroid* markedForSplit;



		//
		//Public Methods
	public:
		AsteroidManager(AsteroidGame* aApplication);
		virtual ~AsteroidManager();

		void update();

		void createAsteroidField();
		std::vector<Asteroid*> getAsteroids() { return iAsteroids;}
		void markAsteroidForSplit(Asteroid* aAsteroid);
		//
		//Private Methods
	private:
		Asteroid* createAsteroid(int aTier);
		Asteroid* createAsteroid(int aTier, Ogre::Vector3 aDirection);
		void placeAsteroid(Asteroid* aAsteroid);
		void placeAsteroid(Asteroid* aAsteroid, Ogre::Vector3 aPosition);
		void splitAsteroid(Asteroid* aAsteroid);

		bool isLegitimateTier(int aTier);

	};
}

#endif//ASTEROID_MANAGER_H_