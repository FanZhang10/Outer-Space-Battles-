#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
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

#include "BoundingBox.h"
#include "Player.h"

namespace AsteroidGame{
	class AsteroidGame; //Forward Declaration
	class Projectile;
	class Asteroid;

	class CollisionManager{
		//
		//Public Variables
	public:
		
		//
		//Private Variables
	private:
		AsteroidGame* iApplication;
		BoundingBox*  iCurrentBoundingBox;
		Player*		  iPlayer;

		//
		//Public Methods
	public:
		CollisionManager(AsteroidGame* aApplication);

		void setBoundingBox(BoundingBox* aBB);
		void setPlayer(Player* aP);

		Ogre::Vector3 checkAtoBBCollision(Asteroid* aAsteroid, Ogre::Vector3 aNewPos);
		Ogre::Vector3 checkAtoPCollision(Asteroid* aAsteroid, Ogre::Vector3 aNewPos);

		bool isProjectileHit(Projectile*);
		bool isLaserAndAsteroidHit(Projectile*);

		//
		//Private Methods
	private:
		float getDistanceFromPlane(Ogre::Vector3 aPoint, Ogre::Vector3 aPlanePoint, Ogre::Vector3 aPlaneNormal);
		Ogre::Vector3 getReflectionVector(Ogre::Vector3 aDirection, Ogre::Vector3 aNormal);
	};
}

#endif//COLLISION_MANAGER_H_