#ifndef VFX_MANAGER_H_
#define VFX_MANAGER_H_
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

	class VFXManager{
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
		VFXManager(OgreApplication* aApplication);
		void update(void);
		//
		//Private Methods
	private:
	};
}

#endif//VFX_MANAGER_H_