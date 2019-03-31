#include "SceneLoader.h"

#include "EntityManager.h"

SceneLoader * SceneLoader::_instance = nullptr;

SceneLoader::SceneLoader() {}

SceneLoader::~SceneLoader()
{
}

SceneLoader * SceneLoader::getInstance()
{
	//If there is no instance, create it
	if (_instance == nullptr) {
		_instance = new SceneLoader();
	}

	return _instance;
}

void SceneLoader::LoadFromJson(nlohmann::json json, Factory<Component> compFactory)
{
	// take the number of entities from JSON
	int _numEntities = json["_numEntities"];

	for (int i = 0; i < _numEntities; i++)
	{
		// for each entity, take the name
		std::string _name = json["_entities"][i]["_entityID"];
		Entity * _newEntity = new Entity(_name);

		// for each entity, take number of its components
		int _numComponents = json["_entities"][i]["_numComponents"];

		for (int j = 0; j < _numComponents; j++)
		{
			// for each component, take the type
			std::string _nameComponent = json["_entities"][i]["_components"][j]["_type"];

			// for each component, how many arguments it has
			int _numArguments = json["_entities"][i]["_components"][j]["_numArguments"];

			// for each component, check what argument it needs
			std::map<std::string, Arguments> _argumentMap;

			Arguments _argument;

			for (int a = 0; a < _numArguments; a++)
			{
				// name of argument
				std::string _nameArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_name"];

				// type of argument
				int _typeArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_type"];

				// argument in string form
				std::string _stringArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_arg"];

				// Conversion to right type
				//1 = int, 2 = float, 3 = double, 4 = string
				switch (_typeArgument)
				{
				case 1:
					_argument.i = std::stoi(_stringArgument);
					_argumentMap[_nameArgument] = Arguments(_argument);
					break;

				case 2:
					_argument.f = std::stof(_stringArgument);
					_argumentMap[_nameArgument] = Arguments(_argument);
					break;

				case 3:
					_argument.d = std::stod(_stringArgument);
					_argumentMap[_nameArgument] = Arguments(_argument);
					break;

				case 4:
					_argument.str = _stringArgument;
					_argumentMap[_nameArgument] = Arguments(_argument);
					break;

				default:
					throw std::invalid_argument("This type of value is not suported");
					break;
				}
			}

			// create component
			Component* _newComponent = compFactory.Create(_nameComponent);

			// init component with arguments
			_newComponent->Init(_argumentMap, _newEntity);

			// add component to entity
			_newEntity->AddComponent(_newComponent);
		}

		// Add entity to Manager
		EntityManager::getInstance()->AddEntity(_newEntity);
	}
}
