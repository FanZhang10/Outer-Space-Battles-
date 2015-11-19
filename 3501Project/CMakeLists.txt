cmake_minimum_required(VERSION 2.6)
 
# Name of project
project(3501Project)

# Specify project files: header files and source files
set(HDRS
	./src/AsteroidGame.h
	./src/ResourceFactory.h
	./src/Asteroid.h
	./src/Player.h
	./src/PlayerManager.h
	./src/AsteroidManager.h
	./src/ProjectileManager.h
	./src/VFXManager.h
	./src/MenuManager.h
	./src/CollisionManager.h
	./src/LevelManager.h
	./src/AssetManager.h
	./src/SoundManager.h
	./src/BoundingBox.h
    ./src/GlobalDebugInitializations.h
    ./src/GlobalExterns.h
)
 
set(SRCS
	./src/AsteroidGame.cpp ./src/main.cpp ./src/MaterialVp.glsl ./src/MaterialFp.glsl ./src/MaterialFile.material
	./src/ShieldVp.glsl ./src/ShieldFp.glsl ./src/Shield.material
	./src/AsteroidVp.glsl ./src/AsteroidFp.glsl ./src/Asteroid.material
	./src/BoundingBoxVp.glsl ./src/BoundingBoxFp.glsl ./src/BoundingBox.material
	./src/ResourceFactory.cpp
	./src/Asteroid.cpp
	./src/Player.cpp
	./src/PlayerManager.cpp
	./src/AsteroidManager.cpp
	./src/ProjectileManager.cpp
	./src/VFXManager.cpp
	./src/MenuManager.cpp
	./src/CollisionManager.cpp
	./src/LevelManager.cpp
	./src/AssetManager.cpp
	./src/SoundManager.cpp
	./src/BoundingBox.cpp
)

# The rules here are specific to Windows Systems
if(WIN32)
    # Get Ogre directory from the environment variable
    set(OGRE_HOME $ENV{OGRE_HOME})

    # Set up Ogre include directories
    include_directories(
        "${OGRE_HOME}/include"
        "${OGRE_HOME}/include/OIS"
        "${OGRE_HOME}/include/OGRE"
        "${OGRE_HOME}/boost"
    )

    # Set up Ogre library directories
    link_directories(
        "${OGRE_HOME}/lib/"
        "${OGRE_HOME}/boost/lib"
    )

    # Applications using Ogre need to be run from inside the Ogre
    # directory. This cmake command needs to come before add_executable
    set(EXECUTABLE_OUTPUT_PATH "${OGRE_HOME}/bin/")

    # Add path name
    configure_file(src/path_config.h.in path_config.h)

    # Add executable based on the source files
    add_executable(3501Project ${HDRS} ${SRCS})

    # Set up names of Ogre libraries
    target_link_libraries(3501Project
        "OgreMain_d.lib"
        "OIS_d.lib"
        "OgreOverlay_d.lib"
    )

    # Avoid ZERO_CHECK target 
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode
    set_target_properties(3501Project PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
