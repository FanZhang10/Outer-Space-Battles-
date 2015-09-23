#ifndef ASTEROID_H_
#define ASTEROID_H_
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

	class Asteroid{

		//Variables
	private:
		//Private Variables
		int iTier;
		int iValue;
		int iHealth;
		double iRadius;
		Ogre::Vector3 iVelocity;
		Ogre::SceneNode* iNode;


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
		Asteroid(int aTier, int aValue, int aHealth, double aRadius, Ogre::SceneNode* aNode);


		void setNode(Ogre::SceneNode* aNode);
		Ogre::SceneNode* getNode();

		void setTier(int);
		int getTier();

		void setValue(int);
		int getValue();

		void setHealth(int);
		int getHealth();

		void setRadius(double);
		double getRadius();
		

	};

}

#endif//ASTEROID_H_