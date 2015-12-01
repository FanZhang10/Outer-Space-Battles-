#include "Projectile.h"
#include "bin/path_config.h"
#include "Player.h"

namespace AsteroidGame{

	Projectile::Projectile(Ogre::SceneNode* aNode, Ogre::Vector3 aPosition, Ogre::Quaternion aDirection,float iSpeed, int type, Player* aPlayer)
	:	iNode(aNode),
		iQuaternion(aDirection),
		iPosition(aPosition),
		iCurrPos(aPosition),
		iStartTime(time(0)),
		iSpeed(iSpeed+0.5f),
		iType(type),
		iPlayer(aPlayer)
	{
		iNode->setPosition(aPosition);
		isActive = true;

		Ogre::Vector3 dir = Ogre::Vector3(1.0, 0, 0);
		iDirection = iQuaternion * dir;

		if (type == 2 || type == 3) 
		{
			iNode->setOrientation(aDirection);
		}

	}

	void Projectile::detach()
	{
		isActive = false;
		iNode->setVisible(false);
	}

	void Projectile::update() {
		if (iType == 0 || iType == 1)
		{
			iNode->translate(iDirection.x *iSpeed, iDirection.y * iSpeed, iDirection.z * iSpeed, Ogre::Node::TS_LOCAL);
		}
		else if(iType == 2 || iType == 3)
		{
			/// change laser positon
			iNode->setPosition(iPlayer->getPostion());
			iNode->setOrientation(iPlayer->getDirection());

		}

	}

	void Projectile::updateLaser()
	{
		iNode->setScale(iLaserLength, 0.1f, 0.1f);
	}

	bool Projectile::isLive()
	{
		float iLocalTime = 0;
		
		if(iType == 0 || iType == 1 )
		{
			iLocalTime = 10.0f;
		}
		else if (iType == 2 )
		{
			iLocalTime = 0.05f;
		}
		else if (iType == 3 )
		{
			iLocalTime = 0.20f;
		}

		time_t now = time(0);

		if((now - iStartTime) > iLocalTime || isActive == false)
		{
			return false;
		}
		else
			return true;
	}

}

