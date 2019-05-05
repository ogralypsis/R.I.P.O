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
	virtual void Update(float deltaTime) = 0;
	virtual void OnEvent(int eventType, Event * e) = 0;
	inline std::string GetId() { return _id; };
	
protected:

	Entity* _ownerEntity;
	std::string _id;
};
#endif