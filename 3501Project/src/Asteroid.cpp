//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, int aTier, Ogre::Vector3 aDirection)
	:	iNode(aNode),
		iDirection(aDirection),
		iTier(aTier),
		iSpeed(0.01)
	{
	}

	void Asteroid::update() {
		//To Do: Move and Rotate Scene Node
		bool safeMove = false;
		Ogre::Vector3 newPos, newDirFinal, newDirBB, newDirP;

		while (!safeMove) {
			newPos = iNode->getPosition() + iDirection*iSpeed;
			newDirBB = aCollisionManager->checkAtoBBCollision(this, newPos);
			newDirP = aCollisionManager->checkAtoPCollision(this, newPos);

			//Collided with Bounding Box
			if (newDirBB != newPos) {
				//Also collided with Player
				if (newDirP != newPos) {
					newDirFinal = (newDirBB + newDirP).normalisedCopy();
				}
				else {
					newDirFinal = newDirBB;
				}
			}
			//Collided with Player
			else if (newDirP != newPos) {
				newDirFinal = newDirP;
			}
			//No collisions found
			else {
				break;
			}

			//Set direction and run collision check again for proposed new direction
			iDirection = newDirFinal;
		}
		
		iNode->setPosition(newPos);
	}

}