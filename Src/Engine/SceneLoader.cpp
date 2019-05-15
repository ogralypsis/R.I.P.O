#include "SceneLoader.h"

#include "EntityManager.h"
#include "EventManager.h"

SceneLoader * SceneLoader::_instance = nullptr;

SceneLoader::SceneLoader() {}

SceneLoader::~SceneLoader() {}

SceneLoader * SceneLoader::GetInstance()
{
	//If there is no instance, create it
	if (_instance == nullptr) {
		_instance = new SceneLoader();
	}

	return _instance;
}

std::map<std::string, Entity*> SceneLoader::LoadFromJson(nlohmann::json json, Factory<Component> compFactory)
{
	// stores the entities that will be instantiated in-game
	std::map<std::string, Entity*> prefabs;

	// take the number of entities from JSON
	int numEntities = json["_numEntities"];

	// Used for saving events' observers read from the JSON
	std::map<std::string, std::vector<Component*>> observers;

	for (int i = 0; i < numEntities; i++)
	{
		// for each entity, take the name
		std::string name = json["_entities"][i]["_entityID"];
		Entity * newEntity = new Entity(name);

		// for each entity, take number of its components
		int numComponents = json["_entities"][i]["_numComponents"];
		


		for (int j = 0; j < numComponents; j++)
		{
			// for each component, take the type
			std::string nameComponent = json["_entities"][i]["_components"][j]["_type"];

			// for each component, how many arguments it has
			int numArguments = json["_entities"][i]["_components"][j]["_numArguments"];

			// for each component, check what argument it needs
			std::map<std::string, Arguments> argumentMap;

			Arguments argument;

			for (int a = 0; a < numArguments; a++)
			{
				// name of argument
				std::string nameArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_name"];

				// type of argument
				int typeArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_type"];

				// argument in string form
				std::string stringArgument = json["_entities"][i]["_components"][j]["_arguments"][a]["_arg"];

				// Conversion to right type
				//1 = int, 2 = float, 3 = double, 4 = string
				switch (typeArgument)
				{
				case 1:
					argument._i = std::stoi(stringArgument);
					argumentMap[nameArgument] = Arguments(argument);
					break;

				case 2:
					argument._f = std::stof(stringArgument);
					argumentMap[nameArgument] = Arguments(argument);
					break;

				case 3:
					argument._d = std::stod(stringArgument);
					argumentMap[nameArgument] = Arguments(argument);
					break;

				case 4:
					argument._str = stringArgument;
					argumentMap[nameArgument] = Arguments(argument);
					break;

				default:
					throw std::invalid_argument("This type of value is not suported");
					break;
				}
			}


			// create component
			Component* newComponent = compFactory.Create(nameComponent);

			// init component with arguments
			newComponent->Init(argumentMap, newEntity);

			// add component to entity
			newEntity->AddComponent(newComponent);

			// for each component, how many events it has
			int numEvents = json["_entities"][i]["_components"][j]["_numEvents"];

			for (int b = 0; b < numEvents; b++) {

				std::string nameEvent = json["_entities"][i]["_components"][j]["_events"][b];

				// Add new observer of a event	
				auto it = observers.find(nameEvent);
				if (it != observers.end())
				{
					it->second.emplace_back(newComponent);
				}
				else
				{
					std::vector<Component*> myVector;
					myVector.emplace_back(newComponent);
					observers.insert(std::pair < std::string, std::vector<Component*>>(nameEvent, myVector));
				}
			}
		}

		if (name == "Bullet")
		{
			//Entity& e = dynamic_cast<Entity&>(*newEntity);
			prefabs.emplace(name, newEntity);
			/*EntityManager::GetInstance()->AddEntity(newEntity);
			EntityManager::GetInstance()->DeleteEntity(newEntity);*/
		}
		
			// Add entity to Manager
			EntityManager::GetInstance()->AddEntity(newEntity);
		
	}

	// passes the listeners to the event manager
	EventManager::GetInstance()->SetJsonObservers(observers);

	return prefabs;
}
