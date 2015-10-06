//
// BoundBox Class
// Encapsulates data and behaviour for a level's outer bounding box

#include "BoundingBox.h"
#include "bin/path_config.h"

namespace AsteroidGame {

	BoundingBox::BoundingBox(Ogre::Vector3 aBounds)
		: iBounds(aBounds)
	{
		//Get iNode data from AssetManager...
		iNode = NULL;
	}

	BoundingBox::~BoundingBox() {
		//Nothing yet
		//How are we cleaning up Node pointers???
	}
}