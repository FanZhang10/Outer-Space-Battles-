//
// Asteroid Class
// Encapsulates data and behaviour for a single asteroid


#include "Asteroid.h"
#include "bin/path_config.h"

namespace Asteroid{

	Asteroid::Asteroid(int aTier, int aValue, int aHealth, double aRadius, Ogre::SceneNode* aNode){
		iTier = aTier;
		iValue = aValue;
		iHealth = aHealth;
		iRadius = aRadius;
		iNode = aNode;
		iVelocity = Ogre::Vector3(0,0,0);
	}

	Ogre::SceneNode* Asteroid::getNode(){
		return iNode;
	}




}