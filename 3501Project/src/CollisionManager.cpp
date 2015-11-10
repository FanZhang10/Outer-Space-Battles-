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
		Ogre::Vector3 boundPos = iCurrentBoundingBox->getNode()->getPosition();

		//printf("boundPos = %d %d %d\n", boundPos.x, boundPos.y, boundPos.z);

		float x = bounds.x;
		float y = bounds.y;
		float z = bounds.z;

		Ogre::Vector3 pl = boundPos + Ogre::Vector3(x,y,z).midPoint(Ogre::Vector3(x,-y,-z));
		Ogre::Vector3 pr = boundPos + Ogre::Vector3(-x,-y,-z).midPoint(Ogre::Vector3(-x,y,z));
		Ogre::Vector3 pu = boundPos + Ogre::Vector3(x,y,z).midPoint(Ogre::Vector3(-x,y,-z));
		Ogre::Vector3 pd = boundPos + Ogre::Vector3(-x,-y,-z).midPoint(Ogre::Vector3(x,-y,z));
		Ogre::Vector3 pf = boundPos + Ogre::Vector3(x,y,z).midPoint(Ogre::Vector3(-x,-y,z));
		Ogre::Vector3 pb = boundPos + Ogre::Vector3(-x,-y,-z).midPoint(Ogre::Vector3(x,y,-z));

		float dl = getDistanceFromPlane(aNewPos, pl, pr);
		float dr = getDistanceFromPlane(aNewPos, pr, pl);
		float du = getDistanceFromPlane(aNewPos, pu, pd);
		float dd = getDistanceFromPlane(aNewPos, pd, pu);
		float df = getDistanceFromPlane(aNewPos, pf, pb);
		float db = getDistanceFromPlane(aNewPos, pb, pf);

		if (dl <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off left wall\n");
			return getReflectionVector(aAsteroid->getDirection(),pr);
		}
		else if (dr <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off right wall\n");
			return getReflectionVector(aAsteroid->getDirection(), pl);
		}
		else if (du <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off up wall\n");
			return getReflectionVector(aAsteroid->getDirection(), pd);
		}
		else if (dd <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off down wall\n");
			return getReflectionVector(aAsteroid->getDirection(), pu);
		}
		else if (df <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off front wall\n");
			return getReflectionVector(aAsteroid->getDirection(), pb);
		}
		else if (db <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off back wall\n");
			return getReflectionVector(aAsteroid->getDirection(), pf);
		}
		else {
			return aNewPos;
		}
	}

	float CollisionManager::getDistanceFromPlane(Ogre::Vector3 aPoint, Ogre::Vector3 aPlanePoint, Ogre::Vector3 aPlaneNormal){
		return aPlaneNormal.dotProduct(aPoint) + (-aPlanePoint).dotProduct(aPlaneNormal);
	}

	Ogre::Vector3 CollisionManager::getReflectionVector(Ogre::Vector3 aDirection, Ogre::Vector3 aNormal){
		//aDirection.normalise();
		Ogre::Vector3 lNormal = aNormal.normalisedCopy();

		printf("New Collision Stats!");
		printf("aDirection = (%f %f %f)\n", aDirection.x, aDirection.y, aDirection.z);
		printf("lNormal = (%f %f %f)\n", lNormal.x, lNormal.y, lNormal.z);

		float dDotN = aDirection.dotProduct(lNormal);
		printf("d.n = (%f)\n", dDotN);
		printf("d.n*2 = (%f)\n", (dDotN*2));

		Ogre::Vector3 sub = (2*dDotN) * lNormal;
		printf("sub = (%f %f %f)\n", sub.x, sub.y, sub.z);

		Ogre::Vector3 newDir(aDirection - (2 * dDotN * lNormal));
		printf("newDir = (%f %f %f)\n", newDir.x, newDir.y, newDir.z);
		return newDir.normalisedCopy();
	}

}