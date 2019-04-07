#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"
#include "Events.h"
#include "ArgumentStruct.h"
#include <map>

class Component
{
public:
	Component();
	~Component();

	virtual void Init(std::map<std::string, Arguments> arguments, Entity* e) = 0;
	virtual void Update() = 0;
	virtual void OnEvent(int eventType, Event e) = 0;
	
protected:
	Entity* _ownerEntity;
};
#endif