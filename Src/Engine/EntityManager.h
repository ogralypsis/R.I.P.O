#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"

class EntityManager
{
public:
	~EntityManager();

	static EntityManager & GetInstance();

	void AddEntity(Entity* e);
	void DeleteEntity(Entity* e);

	void CreateEntity(std::string name, std::vector<Component*> components);

	void Update();
	
	std::vector<Entity*> GetEntities() { return _entities; }

	void GetJsonObservers(const std::map<std::string /*Event*/, std::vector<Component*>> observers);
	std::map<std::string /*Event*/, std::vector<Component*>> GetObservers();

private:
	EntityManager();

	static EntityManager* _instance;
	std::vector<Entity*> _entities;

	std::map<std::string /*Event*/, std::vector<Component*>> _observersJSON;
};
#endif
