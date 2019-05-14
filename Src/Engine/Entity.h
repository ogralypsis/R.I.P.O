#ifndef ENTITY_H
#define ENTITY_H
///<summary>
/// Container of components
///</summary>

#include <string>
#include <vector>

class Component;

class Entity
{
public:
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
	/// Calls the components' own Update() but only those who has RigidBodyComponent
	/// because physics has to be updated before simulating scene physics and updating the rest components
	///</summary>
	///<param name="deltaTime"> time passed since function was last called </param>
	///<param name="physicComponent"> name of the component the entity must have to call it's update </param>
	void UpdatePhysics(float deltaTime, std::string physicComponent);

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
	Component* GetComponent(std::string id);

	///<summary>
	/// Check if the entity has the specified component 
	///</summary>
	///<param name="c">The component to be found</param>  
	///<returns> True if has the specified component </returns>
	bool HasComponent(std::string id);

protected:
	///<summary>
	/// Components the entity owns and give it its funcionality
	///</summary>
	std::vector<Component*> _components;
	
	///<summary>
	/// Unique identifier for each entity
	///</summary>
	std::string _id;
};
#endif
