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

namespace ResourceFactory {

	const std::string iPlayerName = "Player";
	const std::string iPlayerMaterial = "ObjectMaterial";
	
	const std::string iTargetName = "Target";
	const std::string iTargetMaterial = "ObjectMaterial";

	static int iNextAsteroidNum = 0; //Move to asteroid manager later
	std::string getNewAsteroidName();
	const std::string iAsteroidMaterial = "ObjectMaterial";

	void createPlayerModel(Ogre::SceneManager*);
	void createTargetModel(Ogre::SceneManager*);
	Ogre::SceneNode* createAsteroidModel(Ogre::SceneManager*, double aRadius);

	Ogre::Vector3 createVector3InRange(Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds);
	
	void createAsteroidField(Ogre::SceneManager*, int aNumAsteroids, Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds, int aStartingSize);


	/* Our exception type */
	class OgreAppException: public std::exception
    {
		private:
		    std::string message_;
	    public:
			OgreAppException(std::string message) : message_(message) {};
			virtual const char* what() const throw() { return message_.c_str(); };
	};
}

#endif //RESOURCE_FACTORY_H_