#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <vector>

class Entity
{
public:
	Entity(std::string id);
	~Entity();

	void AddComponent(Component* c);
	void DeleteComponent(Component* c);

	void Update();

protected:
	std::vector<Component*> _components;
	std::string _id;
};
#endif