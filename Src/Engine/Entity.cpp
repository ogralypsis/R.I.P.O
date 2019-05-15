#include "Entity.h"
#include "Component.h"

Entity::Entity(std::string id) : _id(id) {}

Entity::~Entity() 
{
	// delete each pointer
	for (std::vector<Component *>::iterator it = _components.begin(); it != _components.end(); ++it)
		delete (*it);
	// clear the vector
	_components.clear();
}

void Entity::AddComponent(Component * c)
{
	// push a new component into the vector
	_components.emplace_back(c);
}

void Entity::DeleteComponent(Component * c)
{
	size_t i = 0;
	bool found = false;
	// search for the component c
	while (!found && i < _components.size()) 
	{
		// when it's found,
		if (_components.at(i) == c) 
		{
			Component* aux = _components.at(i);
			// delete the reference from the vector
			_components.erase(_components.begin() + i);
			// delete the pointer
			delete aux;
			// update flag
			found = true;
		}
		else
		// keep searching
			i++;
	}
}

//searches for a component and returns it if found
Component* Entity::GetComponent(std::string id)
{	
	size_t i = 0;
	
	while (i < _components.size())
	{		
		if (_components[i]->GetId() == id) 
		{
			return _components[i];
		}
		i++;
	}

	return nullptr;
}

bool Entity::HasComponent(std::string id)
{
	size_t i = 0;

	while (i < _components.size())
	{
		if (_components[i]->GetId() == id)
		{
			return true;
		}
		i++;
	}

	return false;
}

std::vector<Component*> Entity::GetAllComponents()
{
	return _components;
}

void Entity::Update(float deltaTime)
{
	// Update each component of the entity
	for (size_t i = 0; i < _components.size(); i++)
		_components.at(i)->Update(deltaTime);
}

void Entity::UpdatePhysics(float deltaTime, std::string physicComponent)
{
	// Update the specified physic component
	for (size_t i = 0; i < _components.size(); i++) {
		if (_components.at(i)->GetId() == physicComponent)
			_components.at(i)->Update(deltaTime);
	}
}

std::string Entity::GetId()
{
	return _id;
}
