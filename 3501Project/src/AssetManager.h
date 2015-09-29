#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_
//
//
//
#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"
#include "ResourceFactory.h"

namespace AsteroidGame{
	class OgreApplication; //Forward Declaration

	class AssetManager{
		//
		//Public Variables
	public:


		//
		//Private Variables
	private:
		OgreApplication* iApplication;
		Ogre::SceneManager *iSceneManager;

		//
		//Public Methods
	public:

		AssetManager(OgreApplication* aApplication);
		void init(Ogre::SceneManager*);
		Ogre::SceneNode* CreatePlayerChassis();
		Ogre::SceneNode* CreatePlayerShield();

		//
		//Private Methods
	private:
	};
}

#endif//ASSET_MANAGER_H_