#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
///<summary>
/// Container of Entities. Manages all entities. Prepared to be singleton
///</summary>

#include <map>
#include "Entity.h"

class EntityManager
{
public:
	~EntityManager();

	///<summary>
	/// Gets the instance of the singleton so it there's only one manager
	///</summary>
	static EntityManager* getInstance();

	///<summary>
	/// Adds new entity to vector of entities in order to keep track of it
	///</summary>
	///<param name="e"> entity to be added to the vector </param>
	void AddEntity(Entity* e);

	///<summary>
	/// deletes entity from vector of entities
	///</summary>
	///<param name="e"> entity to be erased from the vector </param>
	void DeleteEntity(Entity* e);

	///<summary>
	/// Deletes all entities from vector
	///</summary>
	void ClearEntities();

	///<summary>
	/// Creates a new entity with id(name) and adds all components to it
	///</summary>
	///<param name="name"> id of new entity </param>
	///<param name="components"> all components to be added to the new entity </param>
	void CreateEntity(std::string name, std::vector<Component*> components);

	///<summary>
	/// Updates all the entities of the vector
	///</summary>
	///<param name="deltaTime"> time since function was last called </param>
	void Update(float deltaTime);

	///<summary>
	/// Calls the physix updates of the entities that have a RigidBody component
	///</summary>
	///<param name="deltaTime"> time passed since function was last called </param>
	void UpdatePhysics(float deltaTime);

	///<summary>
	/// stores the listeners into the map of the singleton
	///</summary>
	///<param name="observers"> map of (event + component that listen to that event) </param>
	void SetJsonObservers(const std::map<std::string, std::vector<Component*>> observers);

	///<summary>
	/// returns the reference of the entity that has that id
	///</summary>
	///<param name="id"> id of the entity that is being looking for </param>
	Entity* GetEntityByName(std::string id);
	
	///<summary>
	/// Returns the map of listeners (event + component that listen to that event)
	///</summary>
	std::map<std::string, std::vector<Component*>> GetObservers();

private:
	///<summary>
	/// constructor is private so it can't be called (only called from GetInstance)
	///</summary>
	EntityManager();

	///<summary>
	/// instance of singleton
	///</summary>
	static EntityManager* _instance;
	///<summary>
	/// vector of entities stored in the singleton
	///</summary>
	std::vector<Entity*> _entities;
	///<summary>
	/// map of listeners (event + component that listen to that event)
	///</summary>
	std::map<std::string, std::vector<Component*>> _observersJSON;
};
#endif
