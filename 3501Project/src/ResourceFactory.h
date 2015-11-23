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
#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgreMeshSerializer.h"
#include "OGRE/OgreException.h"
#include "OIS/OIS.h"


namespace AsteroidGame {
	class AsteroidGame; //Forward Declaration

	class ResourceFactory {
	public:
		ResourceFactory();
		virtual ~ResourceFactory();

		//Can we replace these SceneManager params with a call to iApplication->getSceneManager()?
		Ogre::SceneNode* createPlayerModel(Ogre::SceneManager*);
		Ogre::SceneNode* createAsteroidModel(Ogre::SceneManager*, float aRadius);
		Ogre::SceneNode* createShieldModel(Ogre::SceneManager*, float aRadius);
		Ogre::SceneNode* createBoundingBoxModel(Ogre::SceneManager*, Ogre::Vector3 aDimensions);
		Ogre::SceneNode* createProjectileModel(Ogre::SceneManager*, long counter, int type);
		
	private:
		int iNextAsteroidNum; //Move to asteroid manager later
		int iNextProjectileNum;
		const std::string iPlayerName;
		const std::string iPlayerMaterial;
		const std::string iShieldName;
		const std::string iShieldMaterial;
		const std::string iAsteroidMaterial;
		const std::string iBoundingBoxMaterial;

		const std::string iPlayerMeshFile;

		const std::string iProjectileMaterial_1;
		const std::string iProjectileMaterial_2;
		Ogre::String particle_material_name_;
		std::string getNewAsteroidName();
	};
}

#endif //RESOURCE_FACTORY_H_