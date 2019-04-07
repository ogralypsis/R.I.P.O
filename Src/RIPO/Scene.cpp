#include "Scene.h"
#include <ArgumentStruct.h>
#include <Component.h>
#include <SceneLoader.h>
#include "RIPOEvent.h"
#include <EventManager.h>

Scene::Scene(std::string ID, Factory<Component> compFactory)
{
	_sceneID = ID;
	_compFactory = compFactory;

	//_instanceEM = EntityManager::GetInstance();
	//_instanceFR = FileReader::getInstance();

	// Read file 
	json entities = FileReader::GetInstance().ReadFile("Assets/" + ID + ".json");

	// Call Loader
	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);

	// *** PROBANDO ***
	AddSceneObservers();
}

Scene::~Scene() {}

void Scene::CreateSceneEntities(nlohmann::json scene)
{
}

void Scene::Update()
{
}
				
void Scene::AddSceneObservers()
{
		std::map<std::string /*Event*/, std::vector<Component*>> observers = EntityManager::GetInstance().GetObservers();
		std::map<std::string, std::vector<Component*>>::const_iterator it = observers.cbegin();

		while (it != observers.cend()) {
			if (it->first == "UpdateTransformEvent") {
				for (int i = 0; i < it->second.size(); i++) 
					EventManager::GetInstance().AddObserver(EventType::EVENT_UPDATE_TRANSFORM, it->second[i]);
								
			}
			else if (it->first == "JEvent") {
				for (int i = 0; i < it->second.size(); i++)
					EventManager::GetInstance().AddObserver(EventType::EVENT_J, it->second[i]);
			}
			else if (it->first == "SEvent") {
				for (int i = 0; i < it->second.size(); i++)
					EventManager::GetInstance().AddObserver(EventType::EVENT_S, it->second[i]);
			}
			// Other events...
			 
			it++;
		}

		

	//}


}
