//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"
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

	void Asteroid::update(CollisionManager* aCollisionManager) {
		//To Do: Move and Rotate Scene Node
		bool safeMove = false;
		Ogre::Vector3 newPos, newDirFinal, newDirBB, newDirP;

		while (!safeMove) {
			newPos = iNode->getPosition() + iDirection*iSpeed;
			newDirBB = aCollisionManager->checkAtoBBCollision(this, newPos);
			newDirP = aCollisionManager->checkAtoPCollision(this, newPos);

			//Collided with Bounding Box
			if (newDirBB != iDirection) {
				//Also collided with Player
				if (newDirP != iDirection) {
					printf("Asteroid collided with Bounding Box AND Player!\n");
					newDirFinal = (newDirBB + newDirP).normalisedCopy();
				}
				else {
					printf("Asteroid collided with Bounding Box!\n");
					newDirFinal = newDirBB;
				}
			}
			//Collided with Player
			else if (newDirP != iDirection) {
				printf("Asteroid collided with Player!\n");
				newDirFinal = newDirP;
			}
			//No collisions found
			else {
				//printf("No collisions found\n");
				break;
			}

			//Set direction and run collision check again for proposed new direction
			iDirection = newDirFinal;
		}
		
		iNode->setPosition(newPos);
	}

}