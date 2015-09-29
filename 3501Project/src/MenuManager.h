#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_
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
	class AsteroidGame; //Forward Declaration

	class MenuManager{
		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		AsteroidGame* iApplication;

		//
		//Public Methods
	public:
		MenuManager(AsteroidGame* aApplication);
		void update(void);
		//
		//Private Methods
	private:

	};
}

#endif//MENU_MANAGER_H_