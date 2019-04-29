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


	///<summary>
	/// Add a component to the entity
	///</summary>
	///<param name="c">The component to be added</param>
	void AddComponent(Component* c);

	///<summary>
	/// Delete the given component from the entity
	///</summary>
	///<param name="c">The component to be deleted</param>  
	void DeleteComponent(Component* c);

	///<summary>
	/// Calls the components' own Update()
	///</summary>
	void Update(float deltaTime);

	///<summary>
	/// Get the entity id
	///</summary>
	///<returns> String id of the entity </returns>
	std::string GetId();

	///<summary>
	/// Search the specified component and returns it if it's found
	///</summary>
	///<param name="c">The component to be returned</param>  
	///<returns> The specified component </returns>
	/*template <class T>
	T* GetComponent(T* c);*/

	Component* GetComponent(Component* c);



protected:

	// Components the entity owns and give it its funcionality
	std::vector<Component*> _components;

	// Unique identifier for each entity
	std::string _id;

	// Determine if the entity is active at the moment
	//bool _active;
};
#endif
