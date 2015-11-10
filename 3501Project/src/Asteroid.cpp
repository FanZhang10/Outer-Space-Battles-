//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"
#include "CollisionManager.h"

#include "GlobalExterns.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, Ogre::Vector3 aDirection, int aTier, double aRadius)
	:	iNode(aNode),
		iDirection(aDirection),
		iTier(aTier),
		iRadius(aRadius),
		iSpeed(0.1)
	{
		printf("Asteroid Created At: %f %f %f\n", aNode->getPosition().x, aNode->getPosition().y, aNode->getPosition().z);
		printf("Asteroid Direction: (%f %f %f)\n", aDirection.x, aDirection.y, aDirection.z);
	}

	void Asteroid::update(CollisionManager* aCollisionManager) {
		//To Do: Move and Rotate Scene Node
		bool safeMove = false;
		Ogre::Vector3 newPos, newDir;

		while (!safeMove) {
			newPos = iNode->getPosition() + iDirection*iSpeed;
			newDir = aCollisionManager->checkAtoBBCollision(this, newPos);

			if (newDir == newPos) {
				break;
			}

			iDirection = newDir;
		}
		
		iNode->setPosition(newPos);
	}

}