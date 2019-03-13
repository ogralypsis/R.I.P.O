#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"

class Entity
{
public:
	Entity();
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
