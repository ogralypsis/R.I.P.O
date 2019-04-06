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

	_instanceEM = EntityManager::getInstance();
	_instanceFR = FileReader::getInstance();

	// Read file 
	json entities = _instanceFR->readFile("Assets/" + ID + ".json");

	// Call Loader
	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);

	// *** PROBANDO ***
	//AddSceneObservers();
}

Scene::~Scene() {}

void Scene::CreateSceneEntities(nlohmann::json scene)
{
}

void Scene::Update()
{
}
				//** HAY QUE COMPROBAR ESTO **//
void Scene::AddSceneObservers()
{
	_auxEntities = EntityManager::getInstance()->GetEntities();

	
	for (int i = 0; i < _auxEntities.size(); i++) {

		std::map<Component*, std::vector<std::string>> component = _auxEntities[i]->GetComponents();

		std::map<Component*, std::vector<std::string>>::const_iterator it = component.cbegin();

		while (it != component.cend()) {

			for (int j = 0; j < it->second.size(); j++) {
				
				if (it->second[j] == "UpdateTransformEvent") {
					UpdateTransformEvent utEvent(0,0,0,0,0);
					EventManager::GetInstance()->AddObserver(utEvent,it->first);
				}
				//....
			}


		}

		

	}


}
