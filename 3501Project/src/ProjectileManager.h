#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_
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

namespace AsteroidGame{
	class OgreApplication; //Forward Declaration

	class ProjectileManager{
		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		OgreApplication* iApplication;

		//
		//Public Methods
	public:
		ProjectileManager(OgreApplication* aApplication);
		void update(void);

		//
		//Private Methods
	private:
	};
}

#endif//PROECTILE_MANAGER_H_