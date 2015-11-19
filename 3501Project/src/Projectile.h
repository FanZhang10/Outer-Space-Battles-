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

	class Projectile{

		//Variables
	private:
		//Private Variables
		Ogre::SceneNode* iNode;
		Ogre::Vector3 iDirection;
		Ogre::Vector3 iPosition;
		Ogre::Vector3 iCurrPos; //collision

		double iRadius; //collision
		double iSpeed;
		time_t iStartTime;
		bool isActive;

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
		Projectile(Ogre::SceneNode* aNode, Ogre::Vector3 aPosition, Ogre::Vector3 aDirection, double iSpeed);

		bool isLive();
		void detach();
		void update();
		
		Ogre::SceneNode* getNode() { return iNode; }

		double getRadius() { return iRadius; }
		
		void setNode(Ogre::SceneNode* aNode) { iNode = aNode; }
		void setRadius(double aRadius) { iRadius = aRadius; } 
		

	};

}

#endif//PROJECTILE_H_