#ifndef SCENE_H
#define SCENE_H

#include <../Engine/Entity.h>
#include <string>

class Scene
{
private: 
	std::vector<Entity*> _entities;
	std::string _sceneID;

public:
	Scene(std::string ID);
	~Scene();

	void Update();

	void addEntity(Entity* ent);

	void deleteEntity(Entity* ent);
};
#endif
