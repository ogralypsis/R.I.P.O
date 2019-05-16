#ifndef SCENE_H
#define SCENE_H

#include <BaseScene.h>

class Scene : public BaseScene
{
public:
	Scene(std::string id, Factory<Component> compFactory);
	~Scene();

	virtual void Update(float t);

	//Returns an instantiated entity with the original parameters read from a JSON file
	//if the entity type has been registered
	Entity* GetPrefab(std::string id);

	//Destroys a specific entity from the scene
	void DestroyEntity(Entity* e);


private:

	virtual void AddSceneObservers();
	
	//factory to create components
	Factory<Component> _factory;

	// registered entities from JSON file
	std::map<std::string, typeOfEntity> _prefabs;
	
	//returns the event type from a string event
	int GetEventType(std::string nameEvent);

	//Creates entity from saved prefabs
	Entity* CreateEntity(std::string id);

	//Removes observers from an entity
	void RemoveObservers(Entity* e);
};
#endif
