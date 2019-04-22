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
	// Create PhysX scene for physics simulation
	MyPhysX::GetInstance().CreateScene();

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

	// empty PhysX scene
	MyPhysX::GetInstance().ClearScene();

	// empty OGRE scene
	MyOgre::GetInstance().ClearScene();

}

void Scene::Update(float t)
{
	// Makes one step in physics simulation
	MyPhysX::GetInstance().StepPhysics(t);

	// Update entities...
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
		// Other events...

		it++;
	}
}