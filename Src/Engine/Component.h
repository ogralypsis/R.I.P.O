#ifndef COMPONENT_H
#define COMPONENT_H
///<summary>
/// USE THIS AS BASE TO CREATE THE COMPONENTS ESPECIFIC TO YOUR APPLICATION
///</summary>

#include "Entity.h"
#include "Events.h"
#include "ArgumentStruct.h"
#include "json.hpp"

#include <map>

class Component
{
public:
	Component();
	~Component();

	///<summary>
	/// Init each component, using the arguments stored in map provided
	/// Always store the entity e as _ownerEntity -> the component will know to which entity it belongs
	///</summary>
	///<param name="arguments"> map of arguments of the component with the name and value of each argument </param>
	///<param name="e"> Entity to which the component belongs </param>
	virtual void Init(std::map<std::string, Arguments> arguments, Entity* e) = 0;

	///<summary>
	/// Virtual update
	///</summary>
	virtual void Update(float deltaTime) = 0;

	///<summary>
	/// This function will be called each time an event to which the component is subscribed, calls its listeners
	///</summary>
	///<param name="eventType"> type of event, especific to the game </param>
	///<param name="e"> event. You can get more information from the event itself from it </param>
	virtual void OnEvent(int eventType, Event * e) = 0;

	///<summary>
	/// returns name of component
	///</summary>
	inline std::string GetId() { return _id; };

	///<summary>
	/// returns name of the entity to which the component belongs
	///</summary>
	inline std::string GetOwnerEntId() { return _ownerEntity->GetId(); };

protected:
	Entity * _ownerEntity;
	std::string _id;
};
#endif
