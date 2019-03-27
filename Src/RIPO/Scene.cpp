#include "Scene.h"

Scene::Scene(std::string ID, Factory<Component, std::string> factory)
{
	_sceneID = ID;
	_factory = factory;

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
	// take the number of entities from JSON
	int _numEntities = scene["_numEntities"];

	for (int i = 0; i < _numEntities; i++) 
	{
		// for each entity, take the name
		std::string _name = scene["_entities"][i]["_entityID"];
		Entity * _newEntity = new Entity(_name);

		// for each entity, take number of its components
		int _numComponents = scene["_entities"][i]["_numComponents"];

		for (int j = 0; j < _numComponents; j++)
		{
			// for each component, take the name
			std::string _nameComponent = scene["_entities"][i]["_components"][j]["_compID"];

			// create component
			Component* _newComponent = _factory.Create(_nameComponent);
			
			// add component to entity
			_newEntity->AddComponent(_newComponent);
		}

		// Add entity to Manager
		_instanceEM->AddEntity(_newEntity);
	}
}

void Scene::Update()
{
}
