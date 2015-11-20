#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_
//
//
//
#include <exception>
#include <string>
#include <vector>
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

namespace AsteroidGame{
	class AsteroidGame; //Forward Declaration
	class Projectile; 

	class ProjectileManager{
		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		AsteroidGame* iApplication;
		std::vector<Projectile*> iProjectiles;
		int type; //choose matrial type
		bool spaceDown;
		long aCounter;
		//
		//Public Methods
	public:
		ProjectileManager(AsteroidGame* aApplication);
		void update(Ogre::SceneManager* ,OIS::Keyboard*, Ogre::Vector3 aPosition, Ogre::Vector3 aDirection, float iSpeed);
		//
		//Private Methods
	private:
		
	};
}

#endif//PROECTILE_MANAGER_H_