#ifndef PLAYER_H_
#define PLAYER_H_
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

	class Player{

		//Variables
	private:
		//Private Variables
		Ogre::Vector3 iVelocity;
		Ogre::SceneNode* iChassisNode;

		float iMaxRollSpeed;
		float iRollAcceleration;
		float iMaxTurnSpeedX;
		float iMaxTurnSpeedY;
		float iMaxSpeed;
		float iTurnDecay;
		float iRollDecay;
		float iSpeedDecay;
		float iAcceleration;

		float iTurnAccelerationX;
		float iTurnAccelerationY;
		float iDesiredTurnSpeedX;
		float iDesiredTurnSpeedY;

		float iSpeed;
		float iRollSpeed;
		float iTurnSpeedX;
		float iTurnSpeedY;
		float iCameraDisplacementX;
		float iCameraDisplacementY;
		float iCameraDisplacementSpeed;


	public:
		//Public Variables
		Ogre::Vector3 getPostion();
		Ogre::Quaternion getDirection();

		//
		//Methods
		//
	private:
		//Private Methods

	public:
		//Public Methods
		Player::Player();

		void setChassisNode(Ogre::SceneNode* aNode);
		Ogre::SceneNode* getChassisNode();

		float getSpeed();

		void update(Ogre::SceneManager* ,OIS::Keyboard* ,OIS::Mouse* );

		void updateOrientation(OIS::Keyboard* ,OIS::Mouse*);
		void updatePosition(OIS::Keyboard* ,OIS::Mouse*);

	};

}

#endif//PLAYER_H_