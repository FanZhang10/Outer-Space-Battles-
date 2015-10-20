//
// Collision Manager
//


#include "CollisionManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"
#include "Asteroid.h"

namespace AsteroidGame{

	CollisionManager::CollisionManager(AsteroidGame* aApplication){
		iApplication = aApplication;
		iCurrentBoundingBox = NULL;
	}

	void CollisionManager::setBoundingBox(BoundingBox* aBB){
		iCurrentBoundingBox = aBB;
	}

	Ogre::Vector3 CollisionManager::checkAtoBBCollision(Asteroid* aAsteroid, Ogre::Vector3 aNewPos){
		if (iCurrentBoundingBox == NULL)
			return aNewPos;

		Ogre::Vector3 bounds = iCurrentBoundingBox->getBounds();

		Ogre::Vector3 pl (bounds.x,0,0);
		Ogre::Vector3 pr (-bounds.x,0,0);
		Ogre::Vector3 pu (bounds.y,0,0);
		Ogre::Vector3 pd (-bounds.y,0,0);
		Ogre::Vector3 pf (bounds.z,0,0);
		Ogre::Vector3 pb (-bounds.z,0,0);

		float dl = getDistanceFromPlane(aNewPos, pl, pr);
		float dr = getDistanceFromPlane(aNewPos, pr, pl);
		float du = getDistanceFromPlane(aNewPos, pu, pd);
		float dd = getDistanceFromPlane(aNewPos, pd, pu);
		float df = getDistanceFromPlane(aNewPos, pf, pb);
		float db = getDistanceFromPlane(aNewPos, pb, pf);

		if (dl <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos,pr);
		}
		else if (dr <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos, pl);
		}
		else if (du <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos, pd);
		}
		else if (dd <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos, pu);
		}
		else if (df <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos, pb);
		}
		else if (db <= aAsteroid->getRadius()) {
			return getReflectionVector(aNewPos, pf);
		}
		else {
			return aNewPos;
		}
	}

	float CollisionManager::getDistanceFromPlane(Ogre::Vector3 aPoint, Ogre::Vector3 aPlanePoint, Ogre::Vector3 aPlaneNormal){
		return aPlaneNormal.dotProduct(aPoint) + (-aPlanePoint).dotProduct(aPlaneNormal);
	}

	Ogre::Vector3 CollisionManager::getReflectionVector(Ogre::Vector3 aDirection, Ogre::Vector3 aNormal){
		return aDirection - ((2 * (aDirection.dotProduct(aNormal))) * aNormal);
	}

}