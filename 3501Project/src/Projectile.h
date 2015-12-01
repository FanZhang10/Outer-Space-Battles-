#ifndef PROJECTILE_H_
#define PROJECTILE_H_
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
#include <time.h> 
#include <iostream>

namespace AsteroidGame {
	class Player;

	class Projectile{

		//Variables
	private:
		//Private Variables
		Ogre::SceneNode* iNode;
		Ogre::Vector3 iDirection;
		Ogre::Quaternion iQuaternion;
		Ogre::Vector3 iPosition;
		Ogre::Vector3 iCurrPos; //collision

		float iRadius; //collision
		float iSpeed;
		time_t iStartTime;
		bool isActive;
		int iType;
		float iLaserLength;
		Player* iPlayer;
	public:
		//Public Variables

		//
		//Methods
		//
	private:
		//Private Methods

	public:
		//Public Methods

		//Constructors
		Projectile(Ogre::SceneNode* aNode, Ogre::Vector3 aPosition, Ogre::Quaternion aDirection, float iSpeed, int type, Player* aplayer);

		bool isLive();
		void detach();
		void update();
		void updateLaser();

		Ogre::SceneNode* getNode() { return iNode; }

		float getRadius() { return iRadius; }
		int  getType() {return iType;}
		void setNode(Ogre::SceneNode* aNode) { iNode = aNode; }
		void setRadius(float aRadius) { iRadius = aRadius; } 
		Ogre::Vector3 getDirection() {return iDirection;}
		Ogre::Vector3 getPostion()  {return  iPosition;}
		void setLaserLength(float aLaserLength) { iLaserLength = aLaserLength;}
	};

}

#endif//PROJECTILE_H_