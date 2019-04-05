#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"

class EntityManager
{
public:
	~EntityManager();

	static EntityManager* getInstance();

	void AddEntity(Entity* e);
	void DeleteEntity(Entity* e);

	void CreateEntity(std::string name, std::vector<Component*> components);

	void Update();
	
	std::vector<Entity*> GetEntities() { return _entities; }

private:
	EntityManager();

	static EntityManager* _instance;
	std::vector<Entity*> _entities;
};
#endif
