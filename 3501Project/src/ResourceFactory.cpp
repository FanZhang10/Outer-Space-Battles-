//
// Resource Factory
// Handles the generation of resources
//
#include "ResourceFactory.h"
#include "bin/path_config.h"
#include "OgreApplication.h"

namespace AsteroidGame{

	void createTargetModel(Ogre::SceneManager* aSceneManager){
		try {
			/* Create a torus
			   The torus is built from a large loop with small circles around the loop */

			Ogre::SceneNode* root_scene_node = aSceneManager->getRootSceneNode();
			
			/* Create the 3D object */
			Ogre::ManualObject* object = NULL;
			object = aSceneManager->createManualObject(iTargetName);
			object->setDynamic(false);

			/* Create triangle list for the object */
			object->begin(iTargetMaterial, Ogre::RenderOperation::OT_TRIANGLE_LIST);

			/* Add vertices to the object */
			Ogre::Vector3 lVertexPosition;
			Ogre::Vector3 lVertexNormal;
			Ogre::ColourValue lVertexColor;
			
			lVertexNormal = Ogre::Vector3(0,0,1);
			lVertexColor = Ogre::ColourValue(1.0,0.0,0.0);

			lVertexPosition = Ogre::Vector3(0,0.2f,1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 


			lVertexPosition = Ogre::Vector3(0,-0.2f,1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 


			lVertexPosition = Ogre::Vector3(0,0,0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,1,0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,1,-0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0.2f,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0.2f,-1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 


			lVertexPosition = Ogre::Vector3(0,-0.2f,-1);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 


			lVertexPosition = Ogre::Vector3(0,0,-0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,-1,0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,-1,-0.2f);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,-0.2f,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			object->triangle(0,1,2);
			object->triangle(3,5,4);
			object->triangle(6,8,7);
			object->triangle(9,10,11);

		
			/* We finished the object */
			object->end();
		
			/* Convert triangle list to a mesh */
			object->convertToMesh(iTargetName);

			/* Create one instance of the torus (one entity) */
			/* The same object can have multiple instances or entities */
			Ogre::Entity* entity = aSceneManager->createEntity(iTargetName);

			/* Apply a material to the entity to give it color */
			/* We already did that above, so we comment it out here */
			/* entity->setMaterialName(material_name); */
			/* But, this call is useful if we have multiple entities with different materials */

			/* Create a scene node for the entity */
			/* The scene node keeps track of the entity's position */
			Ogre::SceneNode* scene_node = root_scene_node->createChildSceneNode(iTargetName);
			scene_node->attachObject(entity);
			//scene_node->setFixedYawAxis(true,Ogre::Vector3(0,1,0));

			/* Position and rotate the entity with the scene node */
			//scene_node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(60));
			//scene_node->rotate(Ogre::Vector3(1, 0, 0), Ogre::Degree(30));
			//scene_node->translate(0.0, 0.0, 0.0);
			scene_node->setPosition(3,0,0);
		}
		catch (Ogre::Exception &e){
			throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
		}
		catch(std::exception &e){
			throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
		}
	}






	Ogre::SceneNode* createPlayerModel(Ogre::SceneManager* aSceneManager){
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


	std::string getNewAsteroidName(){
		std::string r = ("Asteroid" + std::to_string(iNextAsteroidNum));
		iNextAsteroidNum++;
		return r;
	}


	Ogre::Vector3 createVector3InRange(Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds){
		Ogre::Vector3 r = Ogre::Vector3((aPositiveBounds.x - aNegativeBounds.x) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.x,
										(aPositiveBounds.y - aNegativeBounds.y) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.y,
										(aPositiveBounds.z - aNegativeBounds.z) * ( (double)rand() / (double)RAND_MAX ) + aNegativeBounds.z);
		return r;
	}


	void createAsteroidField(Ogre::SceneManager* aSceneManager, int aNumAsteroids, Ogre::Vector3 aPositiveBounds, Ogre::Vector3 aNegativeBounds, int aStartingSize){

		for(int i = 0; i < aNumAsteroids; i++){
			Ogre::SceneNode* lSceneNode;
			double aRadius = (5.0 - 2.0) * ( (double)rand() / (double)RAND_MAX ) + 2.0;
			lSceneNode = createAsteroidModel(aSceneManager, aRadius);
			lSceneNode->setPosition(createVector3InRange(aPositiveBounds, aNegativeBounds));
		}

		
	}


	Ogre::SceneNode* createAsteroidModel(Ogre::SceneManager* aSceneManager, double aRadius){
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
			
			lVertexNormal = Ogre::Vector3(0,0,1);
			lVertexColor = Ogre::ColourValue(0.5f,0.4f,0.3f);

			lVertexPosition = Ogre::Vector3(aRadius,0,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0,aRadius);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(-aRadius,0,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,0,-aRadius);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,aRadius,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
			object->colour(lVertexColor); 

			lVertexPosition = Ogre::Vector3(0,-aRadius,0);

			object->position(lVertexPosition);
			object->normal(lVertexNormal);
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
	

}