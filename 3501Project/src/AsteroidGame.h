#ifndef ASTEROID_GAME_H
#define ASTEROID_GAME_H

//STL
#include <exception>
#include <string>

//Ogre files
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

//Managers
#include "AssetManager.h"
#include "AsteroidManager.h"
#include "CollisionManager.h"
#include "LevelManager.h"
#include "MenuManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
#include "SoundManager.h"
#include "VFXManager.h"

//Other 
#include "ResourceFactory.h"

namespace AsteroidGame {

	typedef std::vector<Ogre::String> Strings;

	enum GameState {StartMenu, Paused, Running, Loading};

	class OgreAppException: public std::exception
    {
		private:
		    std::string message_;
	    public:
			OgreAppException(std::string message) : message_(message) {};
			virtual const char* what() const throw() { return message_.c_str(); };
	};

	class AsteroidGame :
	    public Ogre::FrameListener,		 // Derive from FrameListener to be able to have render event callbacks
        public Ogre::WindowEventListener // Derive from FrameListener to be able to have window event callbacks
		{

        public:
            AsteroidGame();
            void Init(); 
			void MainLoop();

			//Manager Getters
			AssetManager* getAssetManager()				{return iAssetManager;}
			AsteroidManager* getAsteroidManager()		{return iAsteroidManager;}
			CollisionManager* getCollisionManager()		{return iCollisionManager;}
			LevelManager* getLevelManager()				{return iLevelManager;}
			MenuManager* getMenuManager()				{return iMenuManager;}
			PlayerManager* getPlayerManager()			{return iPlayerManager;}
			ProjectileManager* getProjectileManager()	{return iProjectileManager;}
			SoundManager* getSoundManager()				{return iSoundManager;}
			VFXManager* getVFXManager()					{return iVFXManager;}

        private:
			//Application Init Functions
			void InitRootNode();
			void InitPlugins();
			void InitRenderSystem();
			void InitWindow();
			void InitViewport();
			void InitEvents();
			void InitOIS();
			void LoadMaterials();
			void InitManagers();

			//Even Handler Functions
			bool frameRenderingQueued(const Ogre::FrameEvent& fe);
			void windowResized(Ogre::RenderWindow* rw);

			//Ogre command root
            std::auto_ptr<Ogre::Root> ogre_root_;
            //Main Ogre window
            Ogre::RenderWindow* ogre_window_;

			//Input
			OIS::InputManager *input_manager_;
			OIS::Mouse *mouse_;
			OIS::Keyboard *keyboard_;

			//Managers
			AssetManager* iAssetManager;
			AsteroidManager* iAsteroidManager;
			CollisionManager* iCollisionManager;
			LevelManager* iLevelManager;
			MenuManager* iMenuManager;
			PlayerManager* iPlayerManager;
			ProjectileManager* iProjectileManager;
			SoundManager* iSoundManager;
			VFXManager* iVFXManager;

			//GameState
			GameState iGameState;

    }; // class AsteroidGame

} // namespace AsteroidGame;

#endif // ASTEROID_GAME_H
