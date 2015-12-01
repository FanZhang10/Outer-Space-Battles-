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
	class AsteroidManager;
	class CollisionManager;

	class Asteroid{

		//Variables
	private:
		//Private Variables
		Ogre::SceneNode* iNode;
		Ogre::Vector3 iDirection;

		int iTier;
		int iValue;
		int iHealth;
		float iRadius;
		float iSpeed;


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
		Asteroid(Ogre::SceneNode* aNode, Ogre::Vector3 aDirection, int aTier, float aRadius);
		~Asteroid();

		void update(AsteroidManager* aAsteroidManager, CollisionManager* aCollisionManager);
		
		Ogre::SceneNode* getNode() { return iNode; }
		Ogre::Vector3 getDirection() { return iDirection; }
		int getTier() { return iTier; }
		int getValue() { return iValue; }
		int getHealth() { return iHealth; }
		float getRadius() { return iRadius; }
		float getSpeed() { return iSpeed; }
		
		void setNode(Ogre::SceneNode* aNode) { iNode = aNode; }
		void setTier(int aTier) { iTier = aTier; }
		void setValue(int aValue) { iValue = aValue; }
		void setHealth(int aHealth) { iHealth = aHealth; }
		void setRadius(float aRadius) { iRadius = aRadius; } 
		void setSpeed(float aSpeed) { iSpeed = aSpeed; }
		

	};

}

#endif//ASTEROID_H_