//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"
#include "AsteroidManager.h"
#include "CollisionManager.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, Ogre::Vector3 aDirection,int aTier, float aRadius)
	:	iNode(aNode),
		iDirection(aDirection.normalisedCopy()),
		iTier(aTier),
		iRadius(aRadius),
		iSpeed(0.1f)
	{
	}

	Asteroid::~Asteroid() {
		iNode->setVisible(false);
	}

	void Asteroid::update(AsteroidManager* aAsteroidManager, CollisionManager* aCollisionManager) {
		//To Do: Move and Rotate Scene Node
		bool safeMove = false;
		Ogre::Vector3 newPos = iNode->getPosition();
		Ogre::Vector3 newDir;

		while (!safeMove) {
			//Player collision tests
			if (aCollisionManager->checkAtoPCollision(this, newPos)) {
				aAsteroidManager->markAsteroidForSplit(this);
				return;
			}


			//Bounding Box collision tests
			newPos += iDirection*iSpeed;
			newDir = aCollisionManager->checkAtoBBCollision(this, newPos);

			//Collided with Bounding Box
			if (newDir != iDirection) {
				printf("Asteroid collided with Bounding Box!\n");
				iDirection = newDir;
			}
			else {
				safeMove = true;
			}			
		}
		
		iNode->setPosition(newPos);
	}

}