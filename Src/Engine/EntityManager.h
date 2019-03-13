#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"

class EntityManager
{
public:
	~EntityManager();

	EntityManager* getInstance();

	void AddEntity(Entity* e);
	void DeleteEntity(Entity* e);

	void Update();

private:
	EntityManager();

	EntityManager* _instance;
	std::vector<Entity*> _entities;
};
#endif
