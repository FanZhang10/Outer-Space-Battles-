//
// Collision Manager
//


#include "CollisionManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"
#include "Asteroid.h"
#include "Projectile.h"

namespace AsteroidGame{

	CollisionManager::CollisionManager(AsteroidGame* aApplication){
		iApplication = aApplication;
		iCurrentBoundingBox = NULL;
	}

	void CollisionManager::setBoundingBox(BoundingBox* aBB){
		iCurrentBoundingBox = aBB;
	}

	void CollisionManager::setPlayer(Player* aP) {
		iPlayer = aP;
	}

	bool CollisionManager::isProjectileHit(Projectile* aProjectile)
	{
		std::vector<Asteroid*> asteroids = iApplication->getAsteroidManager()->getAsteroids();

		std::vector<Asteroid*>::iterator aPtr = asteroids.begin();

		Ogre::AxisAlignedBox projectileBox = aProjectile->getNode()->_getWorldAABB();

		for (; aPtr != asteroids.end(); aPtr++)
		{
			 Ogre::AxisAlignedBox asteroidBox = (*aPtr)->getNode()->_getWorldAABB();

			 Ogre::AxisAlignedBox asteroidHalfBox((asteroidBox.getCenter() - asteroidBox.getHalfSize() / 2.0f), (asteroidBox.getCenter() + asteroidBox.getHalfSize() / 2.0f));
			 if (asteroidHalfBox.intersects(projectileBox) == true)
			 {
				 //std::cout <<""<<asteroidBox.getSize()<<std::endl;
				
				 std::cout <<"== asteroidBox =="<<asteroidBox.getSize()<<std::endl;
				 std::cout <<"== asteroidHalfBox =="<<asteroidHalfBox.getSize()<<std::endl;
				
				 iApplication->getAsteroidManager()->markAsteroidForSplit(*aPtr);

				return true;
			 }

		}

		return false;
	}

	bool CollisionManager::isLaserAndAsteroidHit(Projectile* aProjectile)
	{
		// methode 1 use OGRE3d Ray

		// methode 2 use distance calc
		std::vector<Asteroid*> asteroids = iApplication->getAsteroidManager()->getAsteroids();
		std::vector<Asteroid*>::iterator aPtr = asteroids.begin();
		Ogre::Vector3 laserPos = aProjectile->getPostion();
		Ogre::Vector3 laserDir = aProjectile->getDirection();

		for (; aPtr != asteroids.end(); aPtr++)
		{
			float radius = (*aPtr)->getRadius();
			Ogre::Vector3 nodePos = (*aPtr)->getNode()->getPosition();
			float dist = laserDir.crossProduct(nodePos - laserPos).length();
		    float laserLength = (nodePos - laserPos).length();
			aProjectile->setLaserLength(laserLength);

			if(dist < radius )
			{
				return true;
			}

		}

		return false;
	}

	Ogre::Vector3 CollisionManager::checkAtoBBCollision(Asteroid* aAsteroid, Ogre::Vector3 aNewPos){
		if (iCurrentBoundingBox == NULL)
			return aAsteroid->getDirection();

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
			return aAsteroid->getDirection();
		}
	}

	bool CollisionManager::checkAtoPCollision(Asteroid* aAsteroid, Ogre::Vector3 aNewPos) {
		if (iPlayer == NULL)
			return false;

		Player* player = iApplication->getPlayerManager()->getPlayer();

		Ogre::Vector3 playerToAsteroidVector = aNewPos - player->getPostion();

		//How big is the player? How can we determine this? This is imprecise as it stands now.
		if (playerToAsteroidVector.length() <= aAsteroid->getRadius() + 0.5f) {
			printf("Asteroid reflected off player\n");
			aAsteroid->setSpeed((aAsteroid->getSpeed() + player->getSpeed())/2);
			return true;
		}
		
		return false;
	}

	float CollisionManager::getDistanceFromPlane(Ogre::Vector3 aPoint, Ogre::Vector3 aPlanePoint, Ogre::Vector3 aPlaneNormal){
		return aPlaneNormal.dotProduct(aPoint) + (-aPlanePoint).dotProduct(aPlaneNormal);
	}

	Ogre::Vector3 CollisionManager::getReflectionVector(Ogre::Vector3 aDirection, Ogre::Vector3 aNormal){
		//aDirection.normalise();
		Ogre::Vector3 lNormal = aNormal.normalisedCopy();

		printf("New Collision Stats!\n");
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