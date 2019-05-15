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

	// The first scene, the menu, doesn't have physics
	if (_id != "0") {
		// empty PhysX scene
		MyPhysX::GetInstance().ClearScene();
	}

	// empty OGRE scene
	MyOgre::GetInstance().ClearScene();

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
	if (_prefabs.count(id) != 0)
		return _prefabs[id];
	else
		return nullptr;
}

Entity* Scene::CreateEntity(std::string id)
{
	// create new entity
	Entity* newEnt = new Entity(id);
	
	std::vector<Component*> components = _prefabs[id]->GetAllComponents();

	for (int i = 0; i < components.size(); i++)
	{
		// create component
		Component* c = _factory.Create(components[i]->GetId());

		// add arguments to components
		c->Init(components[i]->GetArguments(), newEnt);

		//add component to 
		newEnt->AddComponent(c);
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