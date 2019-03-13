#ifndef COMPONENT_H
#define COMPONENT_H

//#include "Entity.h"
#include "Observer.h"
#include <string>

class Entity;

class Component : Observer
{
public:
	Component(std::string id, Entity* e);
	~Component();
	virtual void Update() = 0;
	
protected:
	std::string _id;
	Entity* _ownerEntity;
};
#endif