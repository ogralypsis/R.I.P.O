#include "Scene.h"
#include <ArgumentStruct.h>
#include <Component.h>
#include <SceneLoader.h>
#include <MyOgre.h>

Scene::Scene(std::string ID, Factory<Component> compFactory)
{
	_sceneID = ID;
	_compFactory = compFactory;

	_instanceEM = EntityManager::getInstance();
	_instanceFR = FileReader::getInstance();

	// Read file 
	json entities = _instanceFR->readFile("Assets/Maps/Map" + ID + "/" + "data_map" + ID + ".json");

	// Call Loader
	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);

	// create map
	MyOgre::GetInstance().CreateEntity("Buildings.mesh", Ogre::Vector3(0, 0, 100), Ogre::Vector3(2, 2, 2), Ogre::Radian(-1.5708));
}

Scene::~Scene() {}

void Scene::Update()
{
}
