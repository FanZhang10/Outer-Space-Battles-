#include "Projectile.h"
#include "bin/path_config.h"


namespace AsteroidGame{

	Projectile::Projectile(Ogre::SceneNode* aNode, Ogre::Vector3 aPosition, Ogre::Vector3 aDirection,float iSpeed)
	:	iNode(aNode),
		iDirection(aDirection),
		iPosition(aPosition),
		iCurrPos(aPosition),
		iStartTime(time(0)),
		iSpeed(iSpeed+0.5f)
	{
		iNode->setPosition(aPosition);
		isActive = true;
	}

	void Projectile::detach()
	{
		isActive = false;
		iNode->setVisible(false);
	}

	void Projectile::update() {
		//time_t t = time(0);
		//float newSp = iSpeed*(t- iStartTime)/10;
		//iNode->translate(iDirection.x * newSp+iPosition.x, iDirection.y * newSp+iPosition.y, iDirection.z * newSp+iPosition.z, Ogre::Node::TS_PARENT);
		iNode->translate(iDirection.x *iSpeed, iDirection.y * iSpeed, iDirection.z * iSpeed, Ogre::Node::TS_LOCAL);
	}

	bool Projectile::isLive()
	{
		time_t now = time(0);

		if((now - iStartTime) > 10.0f || isActive == false)
		{
			return false;
		}
		else
			return true;
	}

}

