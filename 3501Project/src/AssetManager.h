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
	class AsteroidGame; //Forward Declaration

	class AssetManager{
		//
		//Public Variables
	public:


		//
		//Private Variables
	private:
		AsteroidGame* iApplication;
		Ogre::SceneManager* iSceneManager;

		ResourceFactory* iResourceFactory;

		Ogre::SceneNode* iPlayerChassis;
		Ogre::SceneNode* iPlayerShield;
		Ogre::SceneNode* iSkybox;

		Ogre::SceneNode* iEngine;
		Ogre::SceneNode* iTurbine;

		//
		//Public Methods
	public:
		AssetManager(AsteroidGame* aApplication);
		virtual ~AssetManager();

		void init(Ogre::SceneManager*);
		
		Ogre::SceneNode* createAsteroid(float aRadius);
		Ogre::SceneNode* createSkybox();
		Ogre::SceneNode* createProjectile(long counter, int type);
		Ogre::SceneNode* createBoundingBox(Ogre::Vector3 aDimensions);
		Ogre::SceneNode* getPlayerChassis() { return iPlayerChassis; }
		Ogre::SceneNode* getPlayerShield()  { return iPlayerShield; }
		Ogre::SceneNode* getSkybox() { return iSkybox; }
		Ogre::SceneNode* getTurbine() { return iTurbine; }
		Ogre::SceneNode* getEngine() { return iEngine; }

		//
		//Private Methods
	private:
	
	};
}

#endif //ASSET_MANAGER_H_