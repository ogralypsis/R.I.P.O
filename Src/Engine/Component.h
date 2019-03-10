#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

class Component
{
public:
	Component(std::string id);
	~Component();
	virtual void Update() = 0;
	
protected:
	std::string _id; 
};
#endif