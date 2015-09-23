#ifndef RESOURCE_FACTORY_H_
#define RESOURCE_FACTORY_H_

#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"


namespace AsteroidGame {

	class OgreApplication;

	const std::string iPlayerName = "Player";
	const std::string iPlayerMaterial = "ObjectMaterial";
	
	const std::string iTargetName = "Target";
	const std::string iTargetMaterial = "ObjectMaterial";

	static int iNextAsteroidNum = 0; //Move to asteroid manager later
	std::string getNewAsteroidName();
	const std::string iAsteroidMaterial = "ObjectMaterial";

	Ogre::SceneNode* createPlayerModel(Ogre::SceneManager*);
	void createTargetModel(Ogre::SceneManager*);
	Ogre::SceneNode* createAsteroidModel(Ogre::SceneManager*, double aRadius);

	Ogre::Vector3 createVector3InRange(Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds);
	
	void createAsteroidField(Ogre::SceneManager*, int aNumAsteroids, Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds, int aStartingSize);

}

#endif //RESOURCE_FACTORY_H_