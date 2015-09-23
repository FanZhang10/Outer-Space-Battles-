#ifndef OGRE_APPLICATION_H_
#define OGRE_APPLICATION_H_

#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"
#include "ResourceFactory.h"

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

namespace AsteroidGame {


	/* A useful type to define */
	typedef std::vector<Ogre::String> Strings;

	/* Our exception type */
	class OgreAppException: public std::exception
    {
		private:
		    std::string message_;
	    public:
			OgreAppException(std::string message) : message_(message) {};
			virtual const char* what() const throw() { return message_.c_str(); };
	};

	/* Our Ogre application */
	class OgreApplication :
	    public Ogre::FrameListener, // Derive from FrameListener to be able to have render event callbacks
        public Ogre::WindowEventListener // Derive from FrameListener to be able to have window event callbacks
		{

        public:
            OgreApplication(void);
            void Init(void); // Call Init() before running the main loop
			void MainLoop(void); // Keep application active

        private:
			// Create root that allows us to access Ogre commands
            std::auto_ptr<Ogre::Root> ogre_root_;
            // Main Ogre window
            Ogre::RenderWindow* ogre_window_;

			// For animating an object
			bool space_down_; // Whether space key was pressed

			// Input managers
			OIS::InputManager *input_manager_;
			OIS::Mouse *mouse_;
			int iOldMouseX;
			int iOldMouseY;
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

			//Manager Getters
			AssetManager* getAssetManager(void){return iAssetManager;}
			AsteroidManager* getAsteroidManager(void){return iAsteroidManager;}
			CollisionManager* getCollisionManager(void){return iCollisionManager;}
			LevelManager* getLevelManager(void){return iLevelManager;}
			MenuManager* getMenuManager(void){return iMenuManager;}
			PlayerManager* getPlayerManager(void){return iPlayerManager;}
			ProjectileManager* getProjectileManager(void){return iProjectileManager;}
			SoundManager* getSoundManager(void){return iSoundManager;}
			VFXManager* getVFXManager(void){return iVFXManager;}

			/* Methods to initialize the application */
			void InitRootNode(void);
			void InitPlugins(void);
			void InitRenderSystem(void);
			void InitWindow(void);
			void InitViewport(void);
			void InitEvents(void);
			void InitOIS(void);
			void LoadMaterials(void);
			void InitManagers(void);


			/* Methods to handle events */
			bool frameRenderingQueued(const Ogre::FrameEvent& fe);
			void windowResized(Ogre::RenderWindow* rw);

    }; // class OgreApplication

} // namespace AsteroidGame;

#endif // OGRE_APPLICATION_H_
