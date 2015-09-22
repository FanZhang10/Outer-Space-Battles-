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

namespace Player {

	class Player{

		//Variables
	private:
		//Private Variables
		Ogre::Vector3 iVelocity;
		Ogre::SceneNode* iChassisNode;

		double iMaxRollSpeed;
		double iRollAcceleration;
		double iMaxTurnSpeedX;
		double iMaxTurnSpeedY;
		double iMaxSpeed;
		double iTurnDecay;
		double iRollDecay;
		double iSpeedDecay;
		double iAcceleration;

		double iTurnAccelerationX;
		double iTurnAccelerationY;
		double iDesiredTurnSpeedX;
		double iDesiredTurnSpeedY;

		double iSpeed;
		double iRollSpeed;
		double iTurnSpeedX;
		double iTurnSpeedY;
		double iCameraDisplacementX;
		double iCameraDisplacementY;
		double iCameraDisplacementSpeed;


	public:
		//Public Variables

		//
		//Methods
		//
	private:
		//Private Methods

	public:
		//Public Methods
		Player::Player();

		//Constructors

		void setChassisNode(Ogre::SceneNode* aNode);
		Ogre::SceneNode* getChassisNode();

		void update(Ogre::SceneManager* ,OIS::Keyboard* ,OIS::Mouse* );


	};

}

#endif//PLAYER_H_