#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include "Entity.h"


class EntityManager
{
public:
	~EntityManager();

	static EntityManager* getInstance();

	void AddEntity(Entity* e);
	void DeleteEntity(Entity* e);
	void ClearEntities();

	void CreateEntity(std::string name, std::vector<Component*> components);

	void Update(float deltaTime);

	void UpdatePhysics(float deltaTime);

	void GetJsonObservers(const std::map<std::string /*Event*/, std::vector<Component*>> observers);
	Entity* GetEntityByName(std::string id);
	
	std::map<std::string /*Event*/, std::vector<Component*>> GetObservers();


private:
	EntityManager();

	static EntityManager* _instance;
	std::vector<Entity*> _entities;

	std::map<std::string /*Event*/, std::vector<Component*>> _observersJSON;
};
#endif
