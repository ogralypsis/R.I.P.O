#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>
#include <Events.h>


class Component;

class Entity
{
public:
	Entity();
	Entity(std::string id);
	~Entity();

	void AddComponent(Component* c, std::vector<std::string> v);

	//void AddComponent(Component* c);
	void DeleteComponent(Component* c);

	void Update();


	std::string GetId();

	template <class T>
	T* GetComponent(T* c);


	std::map<Component*, std::vector<std::string>> GetComponents() { return _components; }

protected:
	//std::vector<Component*> _components;

	std::map<Component*, std::vector<std::string>> _components;
	// Ahora cada componente va acompañado de una lista de eventos a los que quiere subscribirse
	std::string _id;
};
#endif
