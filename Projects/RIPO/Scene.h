#pragma once

#include <Entity.h>
#include <vector>
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

