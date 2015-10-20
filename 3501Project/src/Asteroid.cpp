//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"
#include "CollisionManager.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, int aTier, Ogre::Vector3 aDirection)
	:	iNode(aNode),
		iDirection(aDirection),
		iTier(aTier),
		iSpeed(0.1)
	{
	}

	void Asteroid::update(CollisionManager* aCollisionManager) {
		//To Do: Move and Rotate Scene Node
		Ogre::Vector3 newPos = iNode->getPosition() + iDirection*iSpeed;
		
		Ogre::Vector3 finalNewPos = aCollisionManager->checkAtoBBCollision(this, newPos);
		
		iNode->setPosition(finalNewPos);
	}

}