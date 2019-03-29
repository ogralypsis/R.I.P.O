#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

class Component;

class Entity
{
public:
	Entity();
	Entity(std::string id);
	~Entity();

	void AddComponent(Component* c);
	void DeleteComponent(Component* c);

	void Update();

	template <class T>
	T* GetComponent(T* c);

protected:
	std::vector<Component*> _components;
	std::string _id;
};
#endif
