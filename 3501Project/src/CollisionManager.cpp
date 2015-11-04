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

		Ogre::Vector3 pl = boundPos + Ogre::Vector3(bounds.x,0,0);
		Ogre::Vector3 pr = boundPos + Ogre::Vector3 (-bounds.x,0,0);
		Ogre::Vector3 pu = boundPos + Ogre::Vector3 (bounds.y,0,0);
		Ogre::Vector3 pd = boundPos + Ogre::Vector3 (-bounds.y,0,0);
		Ogre::Vector3 pf = boundPos + Ogre::Vector3 (bounds.z,0,0);
		Ogre::Vector3 pb = boundPos + Ogre::Vector3 (-bounds.z,0,0);

		float dl = getDistanceFromPlane(aNewPos, pl, pr);
		float dr = getDistanceFromPlane(aNewPos, pr, pl);
		float du = getDistanceFromPlane(aNewPos, pu, pd);
		float dd = getDistanceFromPlane(aNewPos, pd, pu);
		float df = getDistanceFromPlane(aNewPos, pf, pb);
		float db = getDistanceFromPlane(aNewPos, pb, pf);

		if (GL_DEBUG_PRINT == TRUE)
			printf("dl = %f\ndr = %f\ndu = %f\ndd = %f\ndf = %f\ndb = %f\n",dl,dr,du,dd,df,db);

		if (dl <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off left wall\n");
			return getReflectionVector(aNewPos,pr);
		}
		else if (dr <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off right wall\n");
			return getReflectionVector(aNewPos, pl);
		}
		else if (du <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off up wall\n");
			return getReflectionVector(aNewPos, pd);
		}
		else if (dd <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off down wall\n");
			return getReflectionVector(aNewPos, pu);
		}
		else if (df <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off front wall\n");
			return getReflectionVector(aNewPos, pb);
		}
		else if (db <= aAsteroid->getRadius()) {
			printf("Asteroid reflected off back wall\n");
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
		aDirection.normalise();
		aNormal.normalise();

		Ogre::Vector3 newDir(aDirection - ((2 * (aDirection.dotProduct(aNormal))) * aNormal));
		
		if(GL_DEBUG_PRINT == TRUE)
			printf("newDir: %f %f %f\n", newDir.x, newDir.y, newDir.z);
		return newDir;
	}

}