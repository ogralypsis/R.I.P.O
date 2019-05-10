#include "EntityManager.h"

EntityManager * EntityManager::_instance = nullptr;
EntityManager::EntityManager() {}

EntityManager::~EntityManager()
{
	ClearEntities();
}

 EntityManager * EntityManager::getInstance()
{
	//If there is no instance, create it
	if (_instance == nullptr) {
		_instance = new EntityManager();
	}
	return _instance;
}

void EntityManager::AddEntity(Entity * e)
{
	// push a new entity into the vector
	_entities.emplace_back(e);
}

void EntityManager::DeleteEntity(Entity * e)
{
	int i = 0;
	bool found = false;
	// search for the entity e
	while (!found && i < _entities.size())
	{
		// when it's found,
		if (_entities.at(i) == e)
		{
			Entity* aux = _entities.at(i);
			// delete the reference from the vector
			_entities.erase(_entities.begin() + i);
			// delete the pointer
			delete aux;
			// update flag
			found = true;
		}
		else
			// keep searching
			i++;
	}
}

void EntityManager::ClearEntities()
{
	// delete each pointer
	for (std::vector<Entity *>::iterator it = _entities.begin(); it != _entities.end(); ++it)
		delete (*it);
	// clear the vector
	_entities.clear();
}

void EntityManager::CreateEntity(std::string name, std::vector<Component*> components)
{
	// Create new entity
	Entity* ent = new Entity(name);

	// Add its components
	for (auto c : components) {
		ent->AddComponent(c);
	}

	AddEntity(ent);
}

void EntityManager::Update(float deltaTime)
{
	// update each entity of the scene
	for (int i = 0; i < _entities.size(); i++)
		_entities.at(i)->Update(deltaTime);
}

void EntityManager::UpdatePhysics(float deltaTime)
{
	for (int i = 0; i < _entities.size(); i++) {

		if (_entities.at(i)->HasComponent("RigidBody"))
			_entities.at(i)->UpdatePhysics(deltaTime);
	}
}

void EntityManager::SetJsonObservers(const std::map<std::string /*Event*/, std::vector<Component*>> observers)
{
	_observersJSON = observers;
}

Entity* EntityManager::GetEntityByName(std::string id)
{
	int i = 0;
	bool found = false;
	Entity* e = nullptr;
	// search for the entity e with name stored in id
	while (!found && i < _entities.size())
	{
		// when it's found,
		if (_entities.at(i)->GetId() == id)
		{
			// get reference to entity
			e = _entities.at(i);
			// update flag
			found = true;
		}
		else
			// keep searching
			i++;
	}
	return e;
}

std::map<std::string, std::vector<Component*>> EntityManager::GetObservers()
{
	return _observersJSON;
}
