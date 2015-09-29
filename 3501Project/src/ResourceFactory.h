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
	class AsteroidGame; //Forward Declaration

	class ResourceFactory {
	public:
		ResourceFactory();
		virtual ~ResourceFactory();

		Ogre::SceneNode* createPlayerModel(Ogre::SceneManager*);
		Ogre::SceneNode* createAsteroidModel(Ogre::SceneManager*, double aRadius);
		Ogre::SceneNode* createShieldModel(Ogre::SceneManager*, double aRadius);
		
	private:
		int iNextAsteroidNum; //Move to asteroid manager later

		const std::string iPlayerName;
		const std::string iPlayerMaterial;
		const std::string iShieldName;
		const std::string iShieldMaterial;
		const std::string iAsteroidMaterial;

		std::string getNewAsteroidName();
	};
}

#endif //RESOURCE_FACTORY_H_