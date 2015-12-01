//
// ProjectileManager
//

#include "ProjectileManager.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"
#include "Projectile.h"
#include "SoundManager.h"

namespace AsteroidGame{

	ProjectileManager::ProjectileManager(AsteroidGame* aApplication)
	{
		iApplication = aApplication;
		aCounter = 0;
		spaceDown = false;
		type = 0;
	}

	void ProjectileManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard, Ogre::Vector3 aPosition, Ogre::Quaternion aDirection,float iSpeed){
		
		if (aKeyboard->isKeyDown(OIS::KC_SPACE)){

			if (spaceDown == false) {
				printf("fire  ");// insert function to implement shooting
				Ogre::SceneNode* lNewProjectNode = iApplication->getAssetManager()->createProjectile(aCounter, type);
				Player* aPlayer = iApplication->getPlayerManager()->getPlayer();
				Projectile* aProjectile = new Projectile(lNewProjectNode, aPosition, aDirection, iSpeed, type, aPlayer);

				aCounter++;
				iProjectiles.push_back(aProjectile);
				if(type == 2 || type == 3)
				{
					iApplication->getSoundManager()->audioPlay(LASERSOUND);
				}else{
					iApplication->getSoundManager()->audioPlay(SHOOTINGSOUND);
				}
	
			}
			spaceDown = true;
		}
		else {
			spaceDown = false;
		}
		//change material
		if(aKeyboard->isKeyDown(OIS::KC_1))
		{
			type = 0;
			
		}
		//change material
		else if(aKeyboard->isKeyDown(OIS::KC_2))
		{
			type = 1;
			
		}
		//change material laser
		else if(aKeyboard->isKeyDown(OIS::KC_3))
		{
			type = 2;
			
		}
		else if(aKeyboard->isKeyDown(OIS::KC_4))
		{
			type = 3;
			
		}
		
		std::vector<Projectile*>::iterator itr = iProjectiles.begin();

		for (; itr != iProjectiles.end(); itr++) 
		{
			//check is live if YES
			if((*itr)->isLive() == true)
			{
				(*itr)->update();

				bool isCollision = false;

				if((*itr)->getType() == 0 || (*itr)->getType() == 1)
				{
					isCollision = iApplication->getCollisionManager()->isProjectileHit((*itr));

					if (isCollision)
					{
						iApplication->getSoundManager()->audioPlay(COLLISIONSOUND);
						(*itr)->detach();
						printf("Bullet hit the asteroid\n");

					}


				}
				else if ((*itr)->getType() == 2 || (*itr)->getType() == 3) {
					if ((*itr)->getType() == 3)
						iApplication->getPlayerManager()->setHealth(1.0f);

					isCollision = iApplication->getCollisionManager()->isLaserAndAsteroidHit((*itr));

					if (isCollision)
					{
						iApplication->getSoundManager()->audioPlay(COLLISIONSOUND);
						(*itr)->updateLaser();
						printf("Bullet hit the Laser\n");
					}
				}


			}
			else 
			{
				//remove sceneNode from the scene
				(*itr)->detach();
			}
		}

	}

}