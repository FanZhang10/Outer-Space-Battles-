#ifndef ASTEROID_MANAGER_H_
#define ASTEROID_MANAGER_H_
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

	class AsteroidManager{
		//
		//Public Variables
	public:
		OgreApplication* iApplication;
		//
		//Private Variables
	private:

		//
		//Public Methods
	public:
		AsteroidManager(OgreApplication* aApplication);
		void update(void);
		//
		//Private Methods
	private:
	};
}

#endif//ASTEROID_MANAGER_H_