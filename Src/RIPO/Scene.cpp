#include "Scene.h"



Scene::Scene(std::string ID)
{
	_sceneID = ID;
}


Scene::~Scene()
{
	// delete pointers
	for (int i = 0; i < _entities.size(); i++) 
	{
		delete(_entities[i]);
	}

	//clear vector
	_entities.clear();
}

void Scene::Update()
{
	//Update all entities
	for (int i = 0; i < _entities.size(); i++) 
	{
		_entities[i]->Update();
	}
}

void Scene::addEntity(Entity * ent)
{
	//Push new entity
	_entities.emplace_back(ent);
}

void Scene::deleteEntity(Entity * ent)
{
	int i = 0;
	bool found = false;

	//Search for the entity
	while (!found && i < _entities.size()) 
	{
		if (_entities[i] == ent) 
		{
			//Delete pointer
			delete(_entities[i]);

			//Clear vector position
			_entities.erase(_entities.begin() + i);

			//End search
			found = true;
		}
		else 
		{
			i++;
		}
	}

}
