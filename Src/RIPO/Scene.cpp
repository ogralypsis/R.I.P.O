#include "Scene.h"
#include <ArgumentStruct.h>
#include <Component.h>
#include <SceneLoader.h>

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
}

Scene::~Scene() {}

void Scene::Update()
{
}
