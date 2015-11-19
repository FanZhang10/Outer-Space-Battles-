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

	void ProjectileManager::update(Ogre::SceneManager* aSceneManager,OIS::Keyboard* aKeyboard, Ogre::Vector3 aPosition, Ogre::Vector3 aDirection,double iSpeed){
		
		if(aKeyboard->isKeyDown(OIS::KC_SPACE)){

			if (spaceDown == false) {
				printf("fire  ");// insert function to implement shooting
				Ogre::SceneNode* lNewProjectNode = iApplication->getAssetManager()->createProjectile(aCounter, type);
				Projectile* aProjectile = new Projectile(lNewProjectNode, aPosition, aDirection, iSpeed);

				aCounter++;
				iProjectiles.push_back(aProjectile);
				iApplication->getSoundManager()->audioPlay(SHOOTINGSOUND);

	
			}
			spaceDown = true;
		}else {
			spaceDown = false;
		}
		//change material
		if(aKeyboard->isKeyDown(OIS::KC_1))
		{
			type = 0;
			
		}
		//change material
		if(aKeyboard->isKeyDown(OIS::KC_2))
		{
			type = 1;
			
		}
		
		
		std::vector<Projectile*>::iterator itr = iProjectiles.begin();

		for (; itr != iProjectiles.end(); itr++) 
		{
			//check is live if YES
			if((*itr)->isLive() == true)
			{
				(*itr)->update();
				if (iApplication->getCollisionManager()->isProjectileHit((*itr)))
				{
					iApplication->getSoundManager()->audioPlay(COLLISIONSOUND);
					(*itr)->detach();
					printf("Bullet hit the asteroid\n");

				}

			}
			else 
			{
				//remove sceneNode from the scene
				(*itr)->detach();
			}
		}
			
		/// remove the timeout item from the vector iProjectiles
	}

}