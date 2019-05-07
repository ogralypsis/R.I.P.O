#include "Scene.h"

// singletons
#include <EntityManager.h>
#include <EventManager.h>
#include <FileReader.h>
#include <SceneLoader.h>
#include <MyOgre.h>
#include <MyPhysX.h>

// events from RIPO
#include "RIPOEvent.h"

Scene::Scene(std::string ID, Factory<Component> compFactory)
{
	_id = ID;

	if (_id != "0") { // The first scene, the menu, doesn't have physics
		// Create PhysX scene for physics simulation
		MyPhysX::GetInstance().CreateScene();
	}

	//SetUp ogre scene
	MyOgre::GetInstance().SetUpScene();

	// Read file 
	json entities = FileReader::getInstance()->readFile("Assets/Maps/Map" + ID + "/" + "data_map" + ID + ".json");

	// Call Loader to create scene
	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);

	// add events to scene
	AddSceneObservers();
}

Scene::~Scene() 
{
	// empty scene from entities
	EntityManager::getInstance()->ClearEntities();

	if (_id != "0") {
		// empty PhysX scene
		MyPhysX::GetInstance().ClearScene();
	}

	// empty OGRE scene
	MyOgre::GetInstance().ClearScene();

}

void Scene::Update(float t)
{
	if (_id != "0") {
		// Makes one step in physics simulation
		MyPhysX::GetInstance().StepPhysics(t);
	}

	// Update entities...
	EntityManager::getInstance()->Update(t);
}

void Scene::AddSceneObservers()
{
	std::map<std::string /*Event*/, std::vector<Component*>> observers = EntityManager::getInstance()->GetObservers();
	std::map<std::string, std::vector<Component*>>::const_iterator it = observers.cbegin();

	while (it != observers.cend()) {
		if (it->first == "UpdateTransformEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_UPDATE_TRANSFORM, it->second[i]);
		}
		else if (it->first == "JEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_J, it->second[i]);
		}
		else if (it->first == "SEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_S, it->second[i]);
		}
		else if (it->first == "WEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_W, it->second[i]);
		}
		else if (it->first == "AEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_A, it->second[i]);
		}
		else if (it->first == "DEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_D, it->second[i]);
		}
		else if (it->first == "PhysicsMoveEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_PHYSICS_MOVE, it->second[i]);
		}
		else if (it->first == "MouseMoveEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_MOVE_MOUSE, it->second[i]);
		}
		// Other events...

		it++;
	}
}