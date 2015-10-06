#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_
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

namespace AsteroidGame {
	
	class BoundingBox {

	public:
		BoundingBox(Ogre::Vector3 aBounds);
		virtual ~BoundingBox();

		Ogre::Vector3 getBounds() { return iBounds; }
		Ogre::SceneNode* getNode() { return iNode; }

		void setNode(Ogre::SceneNode* aNode) { iNode = aNode; }

	private:
		Ogre::Vector3 iBounds;
		Ogre::SceneNode* iNode;
	};
}

#endif