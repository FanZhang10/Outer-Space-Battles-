//
// Collision Manager
//


#include <vector>
#include <OgreSceneNode.h>
#include "CollisionManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"
#include "Projectile.h"

namespace AsteroidGame{

	CollisionManager::CollisionManager(AsteroidGame* aApplication){
		iApplication = aApplication;
	}

	bool CollisionManager::isProjectileHit(Projectile* aProjectile)
	{
		std::vector<Asteroid*> iAsteroids = iApplication->getAsteroidManager()->getAsteroids();

		std::vector<Asteroid*>::iterator iAptr = iAsteroids.begin();

		Ogre::AxisAlignedBox projectielBox = aProjectile->getNode()->_getWorldAABB();

		for (; iAptr != iAsteroids.end(); iAptr++)
		{
			 Ogre::AxisAlignedBox asteroidBox = (*iAptr)->getNode()->_getWorldAABB();
			 Ogre::AxisAlignedBox asteroidHalfBox((asteroidBox.getCenter() - asteroidBox.getHalfSize()), (asteroidBox.getCenter() + asteroidBox.getHalfSize()));
			 if (asteroidHalfBox.intersects(projectielBox)== true)
			 {
				 //std::cout <<""<<asteroidBox.getSize()<<std::endl;
				
				 std::cout <<"== asteroidBox =="<<asteroidBox.getSize()<<std::endl;
				 std::cout <<"== asteroidHalfBox =="<<asteroidHalfBox.getSize()<<std::endl;
				
				return true;
			 }

		}

		return false;
	}

}