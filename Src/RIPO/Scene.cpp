#include "Scene.h"
#include "../Engine/FileReader.h"



Scene::Scene(std::string ID)
{
	_sceneID = ID;

	instanceEM = EntityManager::getInstance();
	instanceFR = FileReader::getInstance();

	// Read file 
	json entities = instanceFR->readFile("Assets/" + ID + ".json");

	CreateSceneEntities(entities);
}


Scene::~Scene()
{
	
}

void Scene::setComponentFactory()
{
	std::string comp = "HealthComponent";

	REGISTER_CLASS(HealthComponent);
}

void Scene::CreateSceneEntities(nlohmann::json entities) {
	std::vector<Component*> components;

	for (int i = 0; i < entities["_numEntities"]; i++) {
		for (int j = 0; j < entities["_entities"][i]["_numComponents"]; j++) {
			//Component* comp = comp_factory.construct(entities["_entities"][i]["_components"][j]);
		}
	}
}

void Scene::Update()
{

}


