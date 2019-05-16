#include "Scene.h"

// singletons Ogre and physX
#include <MyOgre.h>
#include <MyPhysX.h>

// events from RIPO
#include "RIPOEvent.h"

Scene::Scene(std::string ID, Factory<Component> compFactory) : BaseScene(ID, compFactory)
{
	// The first scene, the menu, doesn't have physics
	if (_id != "0") { 
		// Create PhysX scene for physics simulation
		MyPhysX::GetInstance().CreateScene();
	}

	json entities = FileReader::GetInstance()->ReadFile("Assets/Maps/Map" + ID + "/" + "data_map" + ID + ".json");

	_prefabs = SceneLoader::GetInstance()->LoadFromJson(entities, compFactory);

	//SetUp ogre scene
	MyOgre::GetInstance().SetUpScene();

	// add events to scene
	AddSceneObservers();

	_factory = compFactory;
}

Scene::~Scene() 
{
	// empty scene from entities
	EntityManager::GetInstance()->ClearEntities();

	// empty events 
	EventManager::GetInstance()->ClearObservers();

	// The first scene, the menu, doesn't have physics
	if (_id != "0") {
		// empty PhysX scene
		MyPhysX::GetInstance().ClearScene();
	}

	// empty OGRE scene
	MyOgre::GetInstance().ClearScene();

	_prefabs.clear();
}

void Scene::Update(float t)
{
	//Update Physics Entities
	EntityManager::GetInstance()->UpdatePhysics(t, "RigidBody");

	// The first scene, the menu, doesn't have physics
	if (_id != "0") {
		// Makes one step in physics simulation
		MyPhysX::GetInstance().StepPhysics(t);
	}
	// Update entities...
	EntityManager::GetInstance()->Update(t);
}

Entity* Scene::GetPrefab(std::string id)
{
	// if the entity is not registered it won't create a new entity
	if (_prefabs.count(id) != 0)
		return CreateEntity(id);
	else
		return nullptr;
}


Entity* Scene::CreateEntity(std::string id)
{
	// create new entity

	Entity* newEnt = new Entity(id);
	std::map<std::string, std::map<std::string, Arguments>>::const_iterator it = _prefabs[id].components.cbegin();

	while (it != _prefabs[id].components.cend())
	{
		//create the new component
		Component* c = _factory.Create(it->first);

		//add arguments and intialise component
		c->Init(it->second, newEnt);

		//add component to entity
		newEnt->AddComponent(c);

		int numEvents = _prefabs[id].events[it->first].size();

		//add events
		for (int i = 0; i < numEvents; i++)
		{
			std::string event = _prefabs[id].events[it->first][i];
			int eventType = GetEventType(event);
			EventManager::GetInstance()->AddObserver(eventType, c);
		}

		it++;
	}

	EntityManager::GetInstance()->AddEntity(newEnt);

	return newEnt;
}

void Scene::AddSceneObservers()
{
	std::map<std::string /*Event*/, std::vector<Component*>> observers = EventManager::GetInstance()->GetObservers();
	std::map<std::string, std::vector<Component*>>::const_iterator it = observers.cbegin();

	while (it != observers.cend()) {
		if (it->first == "UpdateTransformEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_UPDATE_TRANSFORM, it->second[i]);
		}
		else if (it->first == "JEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_J, it->second[i]);
		}
		else if (it->first == "DeathEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_DEATH, it->second[i]);
		}
		else if (it->first == "SEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_S, it->second[i]);
		}
		else if (it->first == "WEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_W, it->second[i]);
		}
		else if (it->first == "AEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_A, it->second[i]);
		}
		else if (it->first == "DEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_D, it->second[i]);
		}
		else if (it->first == "PhysicsMoveEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_PHYSICS_MOVE, it->second[i]);
		}
		else if (it->first == "MouseMoveEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_MOVE_MOUSE, it->second[i]);
		}
		else if (it->first == "RotationEvent") {
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_ROTATION, it->second[i]);
		}
		else if (it->first == "ShootEvent")
		{
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_SHOOT, it->second[i]);
		}
		else if (it->first == "L_MouseEvent")
		{
			for (int i = 0; i < it->second.size(); i++)
				EventManager::GetInstance()->AddObserver(EventType::EVENT_LEFT_MOUSECLICK, it->second[i]);
		}
		// Other events...

		it++;
	}
}

int Scene::GetEventType(std::string nameEvent)
{
	if (nameEvent == "UpdateTransformEvent")return EventType::EVENT_UPDATE_TRANSFORM;
	else if (nameEvent == "PhysicsMoveEvent")return EventType::EVENT_PHYSICS_MOVE;
	else if (nameEvent == "RotationEvent")return EventType::EVENT_ROTATION;
	else if (nameEvent == "L_MouseEvent")return EventType::EVENT_LEFT_MOUSECLICK;
	else if (nameEvent == "MouseMoveEvent")return EventType::EVENT_MOVE_MOUSE;
	else if (nameEvent == "DeathEvent")return EventType::EVENT_DEATH;
	else if (nameEvent == "WEvent")return EventType::EVENT_W;
	else if (nameEvent == "AEvent")return EventType::EVENT_A;
	else if (nameEvent == "SEvent")return EventType::EVENT_S;
	else if (nameEvent == "DEvent")return EventType::EVENT_D;
	else if (nameEvent == "JEvent") return EventType::EVENT_J;
	else return EventType::EVENT_SHOOT;
}