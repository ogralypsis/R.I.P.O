#include "Scene.h"

// singletons
/*#include <EntityManager.h>
#include <EventManager.h>
#include <FileReader.h>
#include <SceneLoader.h>*/
#include <MyOgre.h>
#include <MyPhysX.h>

// events from RIPO
#include "RIPOEvent.h"

Scene::Scene(std::string ID, Factory<Component> compFactory) : BaseScene(ID, compFactory)
{
	
	if (_id != "0") { // The first scene, the menu, doesn't have physics

		// Create PhysX scene for physics simulation
		MyPhysX::GetInstance().CreateScene();
	}

	json entities = FileReader::getInstance()->readFile("Assets/Maps/Map" + ID + "/" + "data_map" + ID + ".json");

	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);

	//SetUp ogre scene
	MyOgre::GetInstance().SetUpScene();

	// add events to scene
	AddSceneObservers();
}

Scene::~Scene() 
{
	// empty scene from entities
	EntityManager::getInstance()->ClearEntities();

	// The first scene, the menu, doesn't have physics
	if (_id != "0") {
		// empty PhysX scene
		MyPhysX::GetInstance().ClearScene();
	}

	// empty OGRE scene
	MyOgre::GetInstance().ClearScene();

}

void Scene::Update(float t)
{
	// The first scene, the menu, doesn't have physics
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
		// Other events...

		it++;
	}
}