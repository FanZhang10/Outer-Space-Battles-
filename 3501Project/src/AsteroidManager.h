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

#include "GlobalDebugInitializations.h"
#include "Asteroid.h"
#include "BoundingBox.h"

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
		std::map<int, double> iTierRadiusMap;
		std::vector<Asteroid*> iAsteroids;

		//
		//Public Methods
	public:
		AsteroidManager(AsteroidGame* aApplication);
		virtual ~AsteroidManager();

		void update();

		void createAsteroidField();

		//
		//Private Methods
	private:
		void createAsteroid(int aTier);
		void placeAsteroid(Asteroid* aAsteroid);
		void placeAsteroid(Asteroid* aAsteroid, Ogre::Vector3 aPosition);

		bool isLegitimateTier(int aTier);

	};
}

#endif//ASTEROID_MANAGER_H_