#include "Scene.h"



Scene::Scene(std::string ID)
{
	_sceneID = ID;

	_instanceEM = EntityManager::getInstance();
	_instanceFR = FileReader::getInstance();

	// Read file 
	json entities = _instanceFR->readFile("Assets/" + ID + ".json");

	CreateSceneEntities(entities);
}


Scene::~Scene()
{
	
}

void Scene::CreateSceneEntities(nlohmann::json scene)
{
}

void Scene::Update()
{
}



