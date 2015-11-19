//
// ProjectileManager
//


#include "Bullet.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"
#include <boost/lexical_cast.hpp>

namespace AsteroidGame{

	Bullet::Bullet(Ogre::SceneManager* sm):_force(),_node(NULL),_ent(NULL),_active(false){
		static int i = 0;
		_node = sm->getRootSceneNode()->createChildSceneNode();
		_ent =  sm->createEntity(std::string("bullet")+boost::lexical_cast<std::string>(i++), "cube.mesh");
		_node->attachObject(_ent);
		_node->setScale(0.1f,0.1f,0.1f);
		_ent->setVisible(false);
	}

	void Bullet::update(){
		_node->translate(_force);
	}
	void Bullet::fire(const Ogre::Vector3 & pos, const Ogre::Vector3 & force)
	{
		_node->setPosition(pos);
		_force= force;
		_node->setVisible(true);
		_active = true;
	}
	bool active(void){}
	bool touch(void){}
	bool burst(void){}
	bool flying(void){}

}