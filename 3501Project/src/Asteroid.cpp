//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"

namespace AsteroidGame{

	Asteroid::Asteroid(Ogre::SceneNode* aNode, int aTier)
	:	iNode(aNode),
		iTier(aTier)
	{
		iVelocity = Ogre::Vector3(0,0,0);
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

	

}