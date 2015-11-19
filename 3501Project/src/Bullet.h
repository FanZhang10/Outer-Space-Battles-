#ifndef BULLET_H_
#define BULLET_H_
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

namespace AsteroidGame{
	class AsteroidGame; //Forward Declaration

	class Bullet{
		//
		//Public Variables
	public:

		//
		//Private Variables
	private:
		AsteroidGame* iApplication;
		Ogre::Vector3 _force;
		Ogre::SceneNode* _node;
		Ogre::Entity* _ent;
		//
		//Public Methods
	public:
		Bullet(Ogre::SceneManager* sm);
		void update(void);
		bool active(void);
		void fire(const Ogre::Vector3 & pos, const Ogre::Vector3 & force);
		bool touch(void);
		bool burst(void);
		bool flying(void);

		//
		//Private Methods
	private:
		bool _active;
	};
}

#endif//PROECTILE_MANAGER_H_