#ifndef SCENE_H
#define SCENE_H

#include <BaseScene.h>

class Scene : public BaseScene
{
public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	virtual void Update(float t);

	Entity* GetPrefab(std::string id);

private:

	virtual void AddSceneObservers();
	Factory<Component> _factory;

	std::map<std::string, typeOfEntity> _prefabs;
	
	int GetEventType(std::string nameEvent);

	Entity* CreateEntity(std::string id);
};
#endif
