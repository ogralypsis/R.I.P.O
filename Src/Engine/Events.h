#ifndef _H_EVENTS_H_
#define _H_EVENTS_H_
///<summary>
/// Specifies where the event has to be sent
///</summary>
enum EventDestination {
	///<summary>
	/// Event only meant to reach the components of the entity in which the event was created
	///</summary>
	ENTITY,
	///<summary>
	/// Event meant to reach every other entity in the scene and the scene itself, but not the entity in which it is created
	///</summary>
	SCENE,
	///<summary>
	/// Event which is read only by the scene class
	///</summary>
	SCENE_ONLY
};

///<summary>
/// Base struct for the events
///</summary>
struct Event
{
	Event(std::string emmitter, int type, EventDestination destination) : _type(type), _emmitter(emmitter), _destination(destination) {};

	///<summary>
	/// Override operator so events can be compared by name
	///</summary>
	bool operator<(const Event &e) const
	{
		return typeid(this).name() <= typeid(e).name();
	}

	///<summary>
	/// Override operator so events can be compared by name
	///</summary>
	bool operator==(const Event &e) const
	{
		return typeid(this).name() == typeid(e).name();
	}

	///<summary>
	/// returns the type of event
	///</summary>
	int GetType() { return _type; };

	///<summary>
	/// returns the name of object that called the event
	///</summary>
	std::string GetEmmitter() { return _emmitter; };

	///<summary>
	/// returns the type of destination
	///</summary>
	EventDestination GetDestination() { return _destination; };

protected:
	///<summary>
	/// type of event
	///</summary>
	int _type;
	///<summary>
	///  name of object that called the event
	///</summary>
	std::string _emmitter;
	///<summary>
	///  type of destination
	///</summary>
	EventDestination _destination;
};
#endif
