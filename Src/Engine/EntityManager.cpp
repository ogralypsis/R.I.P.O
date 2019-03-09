#include "EntityManager.h"

EntityManager::EntityManager() {}

EntityManager::~EntityManager()
{
	// delete each pointer
	for (std::vector<Entity *>::iterator it = _entities.begin(); it != _entities.end(); ++it)
		delete (*it);
	// clear the vector
	_entities.clear();
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

void EntityManager::Update()
{
	// update each entity of the scene
	for (int i = 0; i < _entities.size(); i++)
		_entities.at(i)->Update();
}
