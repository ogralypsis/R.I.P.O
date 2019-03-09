#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void AddEntity(Entity* e);
	void DeleteEntity(Entity* e);

	void Update();

private:
	std::vector<Entity*> _entities;
};
#endif
