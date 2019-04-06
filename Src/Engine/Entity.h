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


	std::string GetId();

	template <class T>
	T* GetComponent(T* c);


protected:
	std::vector<Component*> _components;
	//std::map<Component*, std::vector<Event>> _components; // Ahora cada componente va acompañado de una lista de eventos a los que quiere subscribirse
	std::string _id;
};
#endif
