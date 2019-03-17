#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"
#include "Events.h"

class Component
{
public:
	Component(std::string id, Entity* e);
	~Component();
	virtual void Update() = 0;
	virtual void OnEvent(Event e) = 0;
	
protected:
	std::string _id;
	Entity* _ownerEntity;
};
#endif