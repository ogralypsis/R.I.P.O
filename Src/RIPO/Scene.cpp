#include "Scene.h"
#include <ArgumentStruct.h>
#include <Component.h>

Scene::Scene(std::string ID, Factory<Component> compFactory)
{
	_sceneID = ID;
	_compFactory = compFactory;

	_instanceEM = EntityManager::getInstance();
	_instanceFR = FileReader::getInstance();

	// Read file 
	json entities = _instanceFR->readFile("Assets/" + ID + ".json");

	CreateSceneEntities(entities);
}

Scene::~Scene() {}

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
			// for each component, take the type
			std::string _nameComponent = scene["_entities"][i]["_components"][j]["_type"];

			// for each component, how many arguments it has
			int _numArguments = scene["_entities"][i]["_components"][j]["_numArguments"];

			// for each component, check what argument it needs
			std::map<std::string, Arguments> _argumentMap;

			for (int a = 0; a < _numArguments; a++)
			{
				std::string _nameArgument = scene["_entities"][i]["_components"][j]["_arguments"][a]["_name"];
				std::string _argument = scene["_entities"][i]["_components"][j]["_arguments"][a]["_arg"];
				
				// esto hay que hacerlo general para cualquier tipo
				_argumentMap[_nameArgument] = Arguments(_argument);
			}

			// create component
			Component* _newComponent = _compFactory.Create(_nameComponent);

			// init component with arguments
			_newComponent->Init(_argumentMap, _newEntity);

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
