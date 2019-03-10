#include "ComponentManager.h"


ComponentManager::ComponentManager()
{
	
}


ComponentManager::~ComponentManager()
{
	for (int i = 0; i < _components.size(); i++)
	{
		delete _components[i]; 
		_components[i] = nullptr;
	}
}

template <class T>
void ComponentManager::AddComponent(T* c)
{
	_components.push_back(c);
}

void ComponentManager::Update()
{
	
}

template <class T>
T* ComponentManager::GetComponent(T* c)
{
	int i = 0; 
	while (i < _components.size())
	{
		if (typeid(components[i] == typeid(c))
		{
			return dynamic_cast<T*>(components[i]);
		}
		i++;
	}

	return nullptr;
}


