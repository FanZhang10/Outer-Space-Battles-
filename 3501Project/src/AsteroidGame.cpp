#include <random>

#include "AsteroidGame.h"
#include "bin/path_config.h"

namespace AsteroidGame {

/* Some configuration constants */
/* They are written here as global variables, but ideally they should be loaded from a configuration file */

/* Initialization */
const Ogre::String config_filename_g = "";
const Ogre::String plugins_filename_g = "";
const Ogre::String log_filename_g = "Ogre.log";

/* Main window settings */
const Ogre::String window_title_g = "3501Project";
const Ogre::String custom_window_capacities_g = "";
const unsigned int window_width_g = 1000;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;

/* Viewport and camera settings */
float viewport_width_g = 0.95f;
float viewport_height_g = 0.95f;
float viewport_left_g = (1.0f - viewport_width_g) * 0.5f;
float viewport_top_g = (1.0f - viewport_height_g) * 0.5f;
unsigned short viewport_z_order_g = 100;
const Ogre::ColourValue viewport_background_color_g(0.0, 0.0, 0.0);
float camera_near_clip_distance_g = 0.01f;
float camera_far_clip_distance_g = 100.0;
Ogre::Vector3 camera_position_g(-5.0, 2.0, 0.0);
Ogre::Vector3 camera_look_at_g(0.0, 0.0, 0.0);
Ogre::Vector3 camera_up_g(0.0, 1.0, 0.0);

/* Materials */
const Ogre::String material_directory_g = (MATERIAL_DIRECTORY  "/src");


AsteroidGame::AsteroidGame(void){
   iGameState = GameState::Loading;
}

//////////////////
//Init Functions//
/////////////////
void AsteroidGame::Init(void){
	input_manager_ = NULL;
	keyboard_ = NULL;
	mouse_ = NULL;

	/* Run all initialization steps */
    InitRootNode();
    InitPlugins();
    InitRenderSystem();
    InitWindow();
    InitViewport();
	InitEvents();
	InitOIS();
	LoadMaterials();

	InitManagers();

	iAsteroidManager->createAsteroidField();

	iGameState = GameState::Running;
}

void AsteroidGame::InitRootNode(void){

    try {
		
		/* We need to have an Ogre root to be able to access all Ogre functions */
        ogre_root_ = std::auto_ptr<Ogre::Root>(new Ogre::Root(config_filename_g, plugins_filename_g, log_filename_g));
		//ogre_root_->showConfigDialog();

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitPlugins(void){

    try {

		/* Load plugin responsible for OpenGL render system */
        Strings plugin_names;
        plugin_names.push_back("RenderSystem_GL");
		
        Strings::iterator iter = plugin_names.begin();
        Strings::iterator iter_end = plugin_names.end();
        for (; iter != iter_end; iter++){
            Ogre::String& plugin_name = (*iter);
            if (OGRE_DEBUG_MODE){
                plugin_name.append("_d");
            }
            ogre_root_->loadPlugin(plugin_name);
        }

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitRenderSystem(void){

    try {

        const Ogre::RenderSystemList& render_system_list = ogre_root_->getAvailableRenderers();
        if (render_system_list.size() == 0)
        {
			throw(OgreAppException(std::string("OgreApp::Exception: Sorry, no rendersystem was found.")));
        }

        Ogre::RenderSystem *render_system = render_system_list.at(0);
        ogre_root_->setRenderSystem(render_system);

    }
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}
      
void AsteroidGame::InitWindow(void){

    try {

        /* Create main window for the application */
		bool create_window_automatically = false;
        ogre_root_->initialise(create_window_automatically, window_title_g, custom_window_capacities_g);

        Ogre::NameValuePairList params;
        params["FSAA"] = "0";
        params["vsync"] = "true";
        ogre_window_ = ogre_root_->createRenderWindow(window_title_g, window_width_g, window_height_g, window_full_screen_g, &params);

        ogre_window_->setActive(true);
        ogre_window_->setAutoUpdated(false);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitViewport(void){

    try {

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = ogre_root_->createSceneManager(Ogre::ST_GENERIC, "MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create camera object */
        Ogre::Camera* camera = scene_manager->createCamera("MyCamera");
        Ogre::SceneNode* camera_scene_node = root_scene_node->createChildSceneNode("MyCameraNode");
        camera_scene_node->attachObject(camera);

        camera->setNearClipDistance(camera_near_clip_distance_g);
        camera->setFarClipDistance(camera_far_clip_distance_g); 

		camera->setPosition(camera_position_g);
		camera->lookAt(camera_look_at_g);
		//camera->setFixedYawAxis(true, camera_up_g);

        /* Create viewport */
        Ogre::Viewport *viewport = ogre_window_->addViewport(camera, viewport_z_order_g, viewport_left_g, viewport_top_g, viewport_width_g, viewport_height_g);

        viewport->setAutoUpdated(true);
        viewport->setBackgroundColour(viewport_background_color_g);

		/* Set aspect ratio */
		float ratio = float(viewport->getActualWidth()) / float(viewport->getActualHeight());
        camera->setAspectRatio(ratio);

    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitEvents(void){

	try {

		/* Add this object as a FrameListener for render events (see frameRenderingQueued event) */
		ogre_root_->addFrameListener(this);

		/* Add this object as a WindowEventListener to handle the window resize event */
		Ogre::WindowEventUtilities::addWindowEventListener(ogre_window_, this);

	}
    catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitOIS(void){

	/* Initialize the Object Oriented Input System (OIS) */
	try {

		/* Initialize input manager */
		OIS::ParamList pl; // Parameter list passed to the input manager initialization
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		ogre_window_->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), 
		std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), 
		std::string("DISCL_NONEXCLUSIVE")));
		input_manager_ = OIS::InputManager::createInputSystem(pl);

		/*size_t hWnd = 0;
		ogre_window_->getCustomAttribute("WINDOW", &hWnd);
		input_manager_ = OIS::InputManager::createInputSystem(hWnd);*/

		/* Initialize keyboard and mouse */
		keyboard_ = static_cast<OIS::Keyboard*>(input_manager_->createInputObject(OIS::OISKeyboard, false));

		mouse_ = static_cast<OIS::Mouse*>(input_manager_->createInputObject(OIS::OISMouse, false));
		unsigned int width, height, depth;
		int top, left;
		ogre_window_->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = mouse_->getMouseState();
		ms.width = width;
		ms.height = height;

	}
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void AsteroidGame::InitManagers(void) {
	iAssetManager = new AssetManager(this);
	iAsteroidManager = new AsteroidManager(this);
	iCollisionManager = new CollisionManager(this);
	iLevelManager = new LevelManager(this);
	iMenuManager = new MenuManager(this);
	iPlayerManager = new PlayerManager(this);
	iProjectileManager = new ProjectileManager(this);
	iSoundManager = new SoundManager(this);
	iVFXManager = new VFXManager(this);

	Ogre::SceneManager* lSceneManager = ogre_root_->getSceneManager("MySceneManager");

	iAssetManager->init(lSceneManager);
	iPlayerManager->init(lSceneManager->getSceneNode("MyCameraNode"));
	iCollisionManager->setBoundingBox(&(iAsteroidManager->iTestBB));
}

void AsteroidGame::LoadMaterials(void){

    try {
		
		/* Load materials that can then be assigned to objects in the scene */
		Ogre::String resource_group_name = "MyGame";
		Ogre::ResourceGroupManager& resource_group_manager = Ogre::ResourceGroupManager::getSingleton();
		resource_group_manager.createResourceGroup(resource_group_name);
		bool is_recursive = false;
		resource_group_manager.addResourceLocation(material_directory_g, "FileSystem", resource_group_name, is_recursive);
		resource_group_manager.initialiseResourceGroup(resource_group_name);
		resource_group_manager.loadResourceGroup(resource_group_name);

	}
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}


///////////////////////////
//Public Helper Functions//
///////////////////////////
Ogre::Vector3 AsteroidGame::createVector3InRange(Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds) {
	/*
	Ogre::Vector3 r = Ogre::Vector3((aPositiveBounds.x - aNegativeBounds.x) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.x,
									(aPositiveBounds.y - aNegativeBounds.y) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.y,
									(aPositiveBounds.z - aNegativeBounds.z) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.z);
	*/
	std::mt19937 rng;
	rng.seed(std::random_device()());

	std::uniform_int_distribution<int> randX ((int)aNegativeBounds.x, (int)aPositiveBounds.x);
	std::uniform_int_distribution<int> randY ((int)aNegativeBounds.y, (int)aPositiveBounds.y);
	std::uniform_int_distribution<int> randZ ((int)aNegativeBounds.z, (int)aPositiveBounds.z);	
	
	return Ogre::Vector3((float)randX(rng), (float)randY(rng), (float)randZ(rng));
}

Ogre::Vector3 AsteroidGame::generateRandomVector3() {
	double randomX = (double)(rand() % 101 - 50) / 50.0;
	double randomY = (double)(rand() % 101 - 50) / 50.0;
	double randomZ = (double)(rand() % 101 - 50) / 50.0;

	return Ogre::Vector3(randomX, randomY, randomZ);
}


///////////////////////
//Main Game Functions//
///////////////////////
void AsteroidGame::MainLoop(void){

    try {
        /* Main loop to keep the application going */

        ogre_root_->clearEventTimes();

        while(!ogre_window_->isClosed()){

            ogre_window_->update(false);

            ogre_window_->swapBuffers();

            ogre_root_->renderOneFrame();

            Ogre::WindowEventUtilities::messagePump();
        }
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

bool AsteroidGame::frameRenderingQueued(const Ogre::FrameEvent& fe){
  
	/* This event is called after a frame is queued for rendering */
	/* Do stuff in this event since the GPU is rendering and the CPU is idle */


	/* Capture input */
	keyboard_->capture();
	mouse_->capture();

	//Update Managers
	if(iGameState == GameState::Running){
		Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
		iPlayerManager->update(scene_manager,keyboard_,mouse_);
		iAsteroidManager->update();
		iProjectileManager->update();
		iVFXManager->update();
	}else if(iGameState == GameState::StartMenu){
		iMenuManager->update();
	}

    return true;
}

void AsteroidGame::windowResized(Ogre::RenderWindow* rw){

	/* Update the window and aspect ratio when the window is resized */
	int width = rw->getWidth(); 
    int height = rw->getHeight();
      
    Ogre::SceneManager* scene_manager = ogre_root_->getSceneManager("MySceneManager");
    Ogre::Camera* camera = scene_manager->getCamera("MyCamera");

	if (camera != NULL){
		camera->setAspectRatio(Ogre::Real(width/height));
    }

	const OIS::MouseState &ms = mouse_->getMouseState();
    ms.width = width;
    ms.height = height;

	ogre_window_->resize(width, height);
	ogre_window_->windowMovedOrResized();
	ogre_window_->update();
}


} // namespace ogre_application;