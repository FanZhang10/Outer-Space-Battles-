//
// Resource Factory
// Handles the generation of resources
//
#include "ResourceFactory.h"
#include "bin/path_config.h"
#include "AsteroidGame.h"

namespace AsteroidGame{
	ResourceFactory::ResourceFactory() :
	iPlayerName("Player"),
	iPlayerMaterial("ObjectMaterial"),
	iShieldName("Target"),
	iShieldMaterial("ShinyBlueMaterial"),
	iAsteroidMaterial("AsteroidMaterial"),
	iNextAsteroidNum(0)
	{
	}

	ResourceFactory::~ResourceFactory() {
	}

	Ogre::SceneNode* ResourceFactory::createPlayerModel(Ogre::SceneManager* aSceneManager){
		try {
			float loop_radius = 0.6f;
			float circle_radius = 0.2f;
			int num_loop_samples = 90;
			int num_circle_samples = 30;
			/* Create a torus
				The torus is built from a large loop with small circles around the loop */


			Ogre::SceneNode* root_scene_node = aSceneManager->getRootSceneNode();
			
			/* Create the 3D object */
			Ogre::ManualObject* object = NULL;
			object = aSceneManager->createManualObject(iPlayerName);
			object->setDynamic(false);

			/* Create triangle list for the object */
			object->begin(iPlayerMaterial, Ogre::RenderOperation::OT_TRIANGLE_LIST);

			/* Add vertices to the object */
			Ogre::Vector3 lVertexPosition;
			Ogre::Vector3 lVertexNormal;
			Ogre::ColourValue lVertexColor;
			
			lVertexNormal = Ogre::Vector3(0,0,1);
			lVertexColor = Ogre::ColourValue(0.8f,0.0,0.0);

			lVertexPosition = Ogre::Vector3(1,0,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexColor = Ogre::ColourValue(0.7f,0.7f,0.7f);

			lVertexPosition = Ogre::Vector3(-1,0.5,0.0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexColor = Ogre::ColourValue(0.5f,0.5f,0.5f);

			lVertexPosition = Ogre::Vector3(-1,0,1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(-1,0,-1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			object->triangle(0,1,2);
			object->triangle(0,3,1);
			object->triangle(0,2,3);
			object->triangle(1,3,2);

		
			/* We finished the object */
			object->end();
		
			/* Convert triangle list to a mesh */
			object->convertToMesh(iPlayerName);

			/* Create one instance of the torus (one entity) */
			/* The same object can have multiple instances or entities */
			Ogre::Entity* entity = aSceneManager->createEntity(iPlayerName);
			/* Apply a material to the entity to give it color */
			/* We already did that above, so we comment it out here */
			/* entity->setMaterialName(material_name); */
			/* But, this call is useful if we have multiple entities with different materials */

			/* Create a scene node for the entity */
			/* The scene node keeps track of the entity's position */
			Ogre::SceneNode* scene_node = root_scene_node->createChildSceneNode(iPlayerName);
			scene_node->attachObject(entity);

			//scene_node->setFixedYawAxis(true,Ogre::Vector3(0,1,0));

			/* Position and rotate the entity with the scene node */
			//scene_node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(60));
			//scene_node->rotate(Ogre::Vector3(1, 0, 0), Ogre::Degree(30));
			//scene_node->translate(0.0, 0.0, 0.0);
			scene_node->setPosition(0,0,0);
			return scene_node;
		}
		catch (Ogre::Exception &e){
			throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
		}
		catch(std::exception &e){
			throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
		}
	}

	Ogre::SceneNode* ResourceFactory::createShieldModel(Ogre::SceneManager* aSceneManager, double aRadius){
		try {
		Ogre::SceneNode* lRootSceneNode = aSceneManager->getRootSceneNode();

		/* Create the 3D object */
		Ogre::ManualObject* object = NULL;
		object = aSceneManager->createManualObject(iShieldName);
		object->setDynamic(false);

		/* Create triangle list for the object */
		object->begin(iShieldMaterial, Ogre::RenderOperation::OT_TRIANGLE_LIST);


		int lNumLoopSamples = 32;
		int lNumCircleSamples = 32;
		/* Add vertices to the object */
		float theta, phi; // Angles for circles
		Ogre::Vector3 lLoopCenter;
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color;
				
		for (int i = 0; i < lNumLoopSamples; i++){ // large loop
			
			theta = Ogre::Math::TWO_PI*i/lNumLoopSamples; // loop sample (angle theta)
			lLoopCenter = Ogre::Vector3(cos(theta), 0, 0); // centre of a small circle

			for (int j = 0; j < lNumCircleSamples; j++){ // small circle
				
				phi = Ogre::Math::TWO_PI*j/lNumCircleSamples; // circle sample (angle phi)
				
				/* Define position, normal and color of vertex */
				Ogre::Vector3 lPosition = lLoopCenter + Ogre::Vector3(0,cos(phi)*sin(theta),sin(phi)*sin(theta));
				vertex_normal = lPosition;
				vertex_position = lPosition*aRadius;
				vertex_color = Ogre::ColourValue(0, 0.6f, 0.8f, 0.3f);

				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < lNumLoopSamples; i++){
			for (int j = 0; j < lNumCircleSamples; j++){
				// Two triangles per quad
				object->triangle(((i + 1) % lNumLoopSamples)*lNumCircleSamples + j, 
									i*lNumLoopSamples + ((j + 1) % lNumLoopSamples),
									i*lNumLoopSamples + j);
				object->triangle(((i + 1) % lNumLoopSamples)*lNumCircleSamples + j,
									((i + 1) % lNumLoopSamples)*lNumCircleSamples + ((j + 1) % lNumCircleSamples),
									i*lNumCircleSamples + ((j + 1) % lNumCircleSamples));
			}
		}
		
		/* We finished the object */
		object->end();
		
		/* Convert triangle list to a mesh */
		object->convertToMesh(iShieldName);

		/* Create one instance of the torus (one entity) */
		/* The same object can have multiple instances or entities */
		Ogre::Entity* entity = aSceneManager->createEntity(iShieldName);

		/* Create a scene node for the entity */
		/* The scene node keeps track of the entity's position */
		Ogre::SceneNode* scene_node = lRootSceneNode->createChildSceneNode(iShieldName);
		scene_node->attachObject(entity);

		return scene_node;
	}
	catch (Ogre::Exception &e){
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
	}
	catch(std::exception &e){
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
	}
	}

	Ogre::SceneNode* ResourceFactory::createAsteroidModel(Ogre::SceneManager* aSceneManager, double aRadius){
		try {
			Ogre::SceneNode* root_scene_node = aSceneManager->getRootSceneNode();
			std::string lAsteroidName = getNewAsteroidName();
			/* Create the 3D object */
			Ogre::ManualObject* object = NULL;
			object = aSceneManager->createManualObject(lAsteroidName);
			object->setDynamic(false);

			/* Create triangle list for the object */
			object->begin(iAsteroidMaterial, Ogre::RenderOperation::OT_TRIANGLE_LIST);

			/* Add vertices to the object */
			Ogre::Vector3 lVertexPosition;
			Ogre::Vector3 lVertexNormal;
			Ogre::ColourValue lVertexColor;
			
			lVertexColor = Ogre::ColourValue(0.5f,0.4f,0.3f);


			lVertexPosition = Ogre::Vector3(aRadius,0,0);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0,aRadius);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(-aRadius,0,0);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0,-aRadius);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,aRadius,0);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,-aRadius,0);

			object->position(lVertexPosition);
			object->normal(lVertexPosition);
			object->colour(lVertexColor); 

			object->triangle(5,0,1);
			object->triangle(5,1,2);
			object->triangle(5,2,3);
			object->triangle(5,3,0);

			object->triangle(4,1,0);
			object->triangle(4,2,1);
			object->triangle(4,3,2);
			object->triangle(4,0,3);

		
			/* We finished the object */
			object->end();
		
			/* Convert triangle list to a mesh */
			object->convertToMesh(lAsteroidName);

			/* Create one instance of the torus (one entity) */
			/* The same object can have multiple instances or entities */
			Ogre::Entity* entity = aSceneManager->createEntity(lAsteroidName);
			/* Apply a material to the entity to give it color */
			/* We already did that above, so we comment it out here */
			/* entity->setMaterialName(material_name); */
			/* But, this call is useful if we have multiple entities with different materials */

			/* Create a scene node for the entity */
			/* The scene node keeps track of the entity's position */
			Ogre::SceneNode* scene_node = root_scene_node->createChildSceneNode(lAsteroidName);
			scene_node->attachObject(entity);


			return scene_node;
		}
		catch (Ogre::Exception &e){
			throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
		}
		catch(std::exception &e){
			throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
		}
		return NULL;

	}

	Ogre::SceneNode* ResourceFactory::createBoundingBoxModel(Ogre::SceneManager* aSceneManager, Ogre::Vector3 aDimensions) {
		try {
			Ogre::SceneNode* root_scene_node = aSceneManager->getRootSceneNode();
			//std::string lAsteroidName = getNewAsteroidName();
			/* Create the 3D object */
			Ogre::ManualObject* object = NULL;
			object = aSceneManager->createManualObject("Bounding Box");
			object->setDynamic(false);

			/* Create triangle list for the object */
			object->begin(iAsteroidMaterial, Ogre::RenderOperation::OT_TRIANGLE_LIST);

			/* Add vertices to the object */
			Ogre::Vector3 lVertexPosition;
			Ogre::Vector3 lVertexNormal;
			Ogre::ColourValue lVertexColor;
			
			lVertexColor = Ogre::ColourValue(0.9f,0.9f,0.9f);

			for (int ix = -1; ix <= 1; ix+=2) {

				for (int iy = -1; iy <= 1; iy+=2) {

					for (int iz = -1; iz <= 1; iz+=2) {
						
						Ogre::Real x = ix * aDimensions.x;
						Ogre::Real y = iy * aDimensions.y;
						Ogre::Real z = iz * aDimensions.z;

						lVertexPosition = Ogre::Vector3(x,y,z);

						printf("Vertice tracked (x,y,z) = (%f,%f,%f)\n", x, y, z);
					
						object->position(lVertexPosition);
						object->normal(lVertexPosition);
						object->colour(lVertexColor); 
					}

				}

			}

			////Inside Rendering
			//Front
			object->triangle(7,5,1);
			object->triangle(7,1,3);
			//Left
			object->triangle(3,1,0);
			object->triangle(3,0,2);
			//Right
			object->triangle(6,4,5);
			object->triangle(6,5,7);
			//Top
			object->triangle(6,7,3);
			object->triangle(6,3,2);
			//Bottom
			object->triangle(5,4,0);
			object->triangle(5,0,1);
			//Back
			object->triangle(2,0,4);
			object->triangle(2,4,6);

			////Outside Rendering
			//Front
			object->triangle(7,3,1);
			object->triangle(7,1,5);
			//Left
			object->triangle(3,2,0);
			object->triangle(3,0,1);
			//Right
			object->triangle(6,7,5);
			object->triangle(6,5,4);
			//Top
			object->triangle(6,2,3);
			object->triangle(6,3,7);
			//Bottom
			object->triangle(5,1,0);
			object->triangle(5,0,4);
			//Back
			object->triangle(2,6,4);
			object->triangle(2,4,0);

		
			/* We finished the object */
			object->end();
		
			/* Convert triangle list to a mesh */
			object->convertToMesh("Bounding Box");

			/* Create one instance of the torus (one entity) */
			/* The same object can have multiple instances or entities */
			Ogre::Entity* entity = aSceneManager->createEntity("Bounding Box");
			/* Apply a material to the entity to give it color */
			/* We already did that above, so we comment it out here */
			/* entity->setMaterialName(material_name); */
			/* But, this call is useful if we have multiple entities with different materials */

			/* Create a scene node for the entity */
			/* The scene node keeps track of the entity's position */
			Ogre::SceneNode* scene_node = root_scene_node->createChildSceneNode("Bounding Box");
			scene_node->attachObject(entity);


			return scene_node;
		}
		catch (Ogre::Exception &e){
			throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
		}
		catch(std::exception &e){
			throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
		}
		return NULL;

	}

	std::string ResourceFactory::getNewAsteroidName(){	
		std::stringstream ss;
		ss << iNextAsteroidNum;
		std::string r = ("Asteroid"+ss.str());
		iNextAsteroidNum++;
		return r;
	}

}