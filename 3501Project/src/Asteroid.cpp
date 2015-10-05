//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, int aTier)
	:	iNode(aNode),
		iTier(aTier),
		iSpeed(0.01)
	{
		//Temporary random direction calc (-1 to 1)
		double randomX = (double)(rand() % 101 - 50) / 50.0;
		double randomY = (double)(rand() % 101 - 50) / 50.0;
		double randomZ = (double)(rand() % 101 - 50) / 50.0;
		printf("Random X Y Z = %f %f %f\n", randomX, randomY, randomZ);
		iVelocity = Ogre::Vector3(randomX,randomY,randomZ).normalisedCopy();
	}
	
	Asteroid::Asteroid(Ogre::SceneNode* aNode, int aTier, int aValue, int aHealth, double aRadius)
	:	iNode(aNode),
		iTier(aTier),
		iValue(aValue),
		iHealth(aHealth),
		iRadius(aRadius)
	{
		iVelocity = Ogre::Vector3(0,0,0);
	}

	void Asteroid::update() {
		//To Do: Move and Rotate Scene Node
		Ogre::Vector3 newPos = iNode->getPosition() + iVelocity*iSpeed;
		iNode->setPosition(newPos);
	}

}