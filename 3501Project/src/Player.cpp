//
// Player Class
// Encapsulates data and behaviour for the Player
//
#include "Player.h"
#include "bin/path_config.h"

namespace AsteroidGame{

	Player::Player(){
		iSpeed = 0;
		iMaxSpeed = .4;
		iSpeedDecay = .005;
		iAcceleration = .02;

		iRollSpeed = 0;
		iRollAcceleration = .25;
		iRollDecay = 0.1;
		iMaxRollSpeed = 2.0;

		iTurnSpeedX = 0;
		iTurnSpeedY = 0;
		iTurnAccelerationX = .3;
		iTurnAccelerationY = .3;
		iDesiredTurnSpeedX = 0;
		iDesiredTurnSpeedY = 0;
		iMaxTurnSpeedX = 2.0;
		iMaxTurnSpeedY = 2.0;
		iTurnDecay = .1;

		iCameraDisplacementX = 0;
		iCameraDisplacementY = 0;
		iCameraDisplacementSpeed = .25;
	}

	void Player::update(Ogre::SceneManager* aSceneManager, OIS::Keyboard* aKeyboard, OIS::Mouse* aMouse){

		Ogre::SceneNode* root_scene_node = aSceneManager->getRootSceneNode();
		Ogre::SceneNode* lPlayerNode = aSceneManager->getSceneNode("Player");


		//Thrust
		if(aKeyboard->isKeyDown(OIS::KC_W)){
			iSpeed += iAcceleration;
			if(iSpeed > iMaxSpeed){
				iSpeed = iMaxSpeed;
			}
		}else{
			iSpeed -= iSpeedDecay;
			if(iSpeed < 0){
				iSpeed = 0;
			}
		}

		lPlayerNode->translate(iSpeed,0,0,Ogre::Node::TS_LOCAL);
		//End Thrust

		//Rolling
		if(aKeyboard->isKeyDown(OIS::KC_A)){
			iRollSpeed -= iRollAcceleration;
			if(iRollSpeed < -iMaxRollSpeed){
				iRollSpeed = -iMaxRollSpeed;
			}
		}else
		if(aKeyboard->isKeyDown(OIS::KC_D)){
			iRollSpeed += iRollAcceleration;
			if(iRollSpeed > iMaxRollSpeed){
				iRollSpeed = iMaxRollSpeed;
			}
		}else{
			if(iRollSpeed > 0+iRollAcceleration){
				iRollSpeed -= iRollDecay;
			}else if(iRollSpeed < 0-iRollAcceleration){
				iRollSpeed += iRollDecay;
			}else{
				iRollSpeed = 0;
			}
		}

		lPlayerNode->pitch(Ogre::Degree(iRollSpeed));
		//End Rolling

		//Turning
		iDesiredTurnSpeedX = ((double)-aMouse->getMouseState().X.rel);
		iDesiredTurnSpeedY = ((double)-aMouse->getMouseState().Y.rel);
		//Adjust according to mouse sensitivity
		iDesiredTurnSpeedX /= 5;
		iDesiredTurnSpeedY /= 5;


		//DesiredTurnSpeedBounds
		if(iDesiredTurnSpeedX > iMaxTurnSpeedX){
			iDesiredTurnSpeedX = iMaxTurnSpeedX;
		}else
		if(iDesiredTurnSpeedX < -iMaxTurnSpeedX){
			iDesiredTurnSpeedX = -iMaxTurnSpeedX;
		}

		if(iDesiredTurnSpeedY > iMaxTurnSpeedY){
			iDesiredTurnSpeedY = iMaxTurnSpeedY;
		}else
		if(iDesiredTurnSpeedY < -iMaxTurnSpeedY){
			iDesiredTurnSpeedY = -iMaxTurnSpeedY;
		}

		//AdjustTurnSpeed
		if(iDesiredTurnSpeedX > iTurnSpeedX){
			iTurnSpeedX += iTurnAccelerationX;
		}
		if(iDesiredTurnSpeedX < iTurnSpeedX){
			iTurnSpeedX -= iTurnAccelerationX;
		}
		if(iDesiredTurnSpeedY > iTurnSpeedY){
			iTurnSpeedY += iTurnAccelerationY;
		}
		if(iDesiredTurnSpeedY < iTurnSpeedY){
			iTurnSpeedY -= iTurnAccelerationY;
		}

		//TurnSpeedBounds
		if(iTurnSpeedX > iMaxTurnSpeedX){
			iTurnSpeedX = iMaxTurnSpeedX;
		}
		if(iTurnSpeedX < -iMaxTurnSpeedX){
			iTurnSpeedX = -iMaxTurnSpeedX;
		}
		if(iTurnSpeedY > iMaxTurnSpeedY){
			iTurnSpeedY = iMaxTurnSpeedY;
		}
		if(iTurnSpeedY < -iMaxTurnSpeedY){
			iTurnSpeedY = -iMaxTurnSpeedY;
		}

		//Zero out turn speeds if turn speeds are low
		if(iTurnSpeedY < iTurnAccelerationY && iTurnSpeedY > -iTurnAccelerationY){
			iTurnSpeedY = 0;
		}
		if(iTurnSpeedX < iTurnAccelerationX && iTurnSpeedX > -iTurnAccelerationX){
			iTurnSpeedX = 0;
		}


		lPlayerNode->yaw(Ogre::Degree(iTurnSpeedX));
		lPlayerNode->roll(Ogre::Degree(iTurnSpeedY));
		//End Mouse Movement

		//Camera Smoothing



		Ogre::SceneNode* lCameraNode = aSceneManager->getSceneNode("MyCameraNode");
		lCameraNode->setPosition(lPlayerNode->getPosition());
		lCameraNode->setOrientation(lPlayerNode->getOrientation());
		lCameraNode->translate(-5-(iSpeed),1+iCameraDisplacementY/4,-iCameraDisplacementX/4,Ogre::Node::TS_LOCAL);
		lCameraNode->roll(Ogre::Degree(15));
		

	}


	
	void Player::updatePosition(OIS::Keyboard* aKeyboard, OIS::Mouse* aMouse){
				//Thrust
		if(aKeyboard->isKeyDown(OIS::KC_W)){
			iSpeed += iAcceleration;
			if(iSpeed > iMaxSpeed){
				iSpeed = iMaxSpeed;
			}
		}else{
			iSpeed -= iSpeedDecay;
			if(iSpeed < 0){
				iSpeed = 0;
			}
		}

		iChassisNode->translate(iSpeed,0,0,Ogre::Node::TS_LOCAL);
	}




	void Player::updateOrientation(OIS::Keyboard* aKeyboard, OIS::Mouse* aMouse){

		//Rolling
		if(aKeyboard->isKeyDown(OIS::KC_A)){
			iRollSpeed -= iRollAcceleration;
			if(iRollSpeed < -iMaxRollSpeed){
				iRollSpeed = -iMaxRollSpeed;
			}
		}else
		if(aKeyboard->isKeyDown(OIS::KC_D)){
			iRollSpeed += iRollAcceleration;
			if(iRollSpeed > iMaxRollSpeed){
				iRollSpeed = iMaxRollSpeed;
			}
		}else{
			if(iRollSpeed > 0+iRollAcceleration){
				iRollSpeed -= iRollDecay;
			}else if(iRollSpeed < 0-iRollAcceleration){
				iRollSpeed += iRollDecay;
			}else{
				iRollSpeed = 0;
			}
		}

		iChassisNode->pitch(Ogre::Degree(iRollSpeed));
		//End Rolling

		//Turning
		iDesiredTurnSpeedX = ((double)-aMouse->getMouseState().X.rel);
		iDesiredTurnSpeedY = ((double)-aMouse->getMouseState().Y.rel);
		//Adjust according to mouse sensitivity
		iDesiredTurnSpeedX /= 5;
		iDesiredTurnSpeedY /= 5;


		//DesiredTurnSpeedBounds
		if(iDesiredTurnSpeedX > iMaxTurnSpeedX){
			iDesiredTurnSpeedX = iMaxTurnSpeedX;
		}else
		if(iDesiredTurnSpeedX < -iMaxTurnSpeedX){
			iDesiredTurnSpeedX = -iMaxTurnSpeedX;
		}

		if(iDesiredTurnSpeedY > iMaxTurnSpeedY){
			iDesiredTurnSpeedY = iMaxTurnSpeedY;
		}else
		if(iDesiredTurnSpeedY < -iMaxTurnSpeedY){
			iDesiredTurnSpeedY = -iMaxTurnSpeedY;
		}

		//AdjustTurnSpeed
		if(iDesiredTurnSpeedX > iTurnSpeedX){
			iTurnSpeedX += iTurnAccelerationX;
		}
		if(iDesiredTurnSpeedX < iTurnSpeedX){
			iTurnSpeedX -= iTurnAccelerationX;
		}
		if(iDesiredTurnSpeedY > iTurnSpeedY){
			iTurnSpeedY += iTurnAccelerationY;
		}
		if(iDesiredTurnSpeedY < iTurnSpeedY){
			iTurnSpeedY -= iTurnAccelerationY;
		}

		//TurnSpeedBounds
		if(iTurnSpeedX > iMaxTurnSpeedX){
			iTurnSpeedX = iMaxTurnSpeedX;
		}
		if(iTurnSpeedX < -iMaxTurnSpeedX){
			iTurnSpeedX = -iMaxTurnSpeedX;
		}
		if(iTurnSpeedY > iMaxTurnSpeedY){
			iTurnSpeedY = iMaxTurnSpeedY;
		}
		if(iTurnSpeedY < -iMaxTurnSpeedY){
			iTurnSpeedY = -iMaxTurnSpeedY;
		}

		//Zero out turn speeds if turn speeds are low
		if(iTurnSpeedY < iTurnAccelerationY && iTurnSpeedY > -iTurnAccelerationY){
			iTurnSpeedY = 0;
		}
		if(iTurnSpeedX < iTurnAccelerationX && iTurnSpeedX > -iTurnAccelerationX){
			iTurnSpeedX = 0;
		}


		iChassisNode->yaw(Ogre::Degree(iTurnSpeedX));
		iChassisNode->roll(Ogre::Degree(iTurnSpeedY));
		//End Mouse Movement

	}

	Ogre::Vector3  Player::getPostion()
	{	
		return iChassisNode->getPosition();
	}

	Ogre::Vector3  Player::getDirection()
	{
		Ogre::Quaternion q = iChassisNode->getOrientation();
		Ogre::Vector3 dir = Ogre::Vector3(1.0, 0, 0);
		Ogre::Vector3 newDir = q * dir;

		return newDir;
	}


	void Player::setChassisNode(Ogre::SceneNode* aSceneNode){
		iChassisNode = aSceneNode;
	}

	Ogre::SceneNode* Player::getChassisNode(){
		return iChassisNode;
	}

	double Player::getSpeed(){
		return iSpeed;
	}
}