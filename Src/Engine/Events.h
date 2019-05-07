#ifndef _H_EVENTS_H_
#define _H_EVENTS_H_

#include <typeinfo>


typedef enum EventDestination {
	// Event only meant to reach the components of the entity in which the event was created
	ENTITY,
	// Event meant to reach every other entity in the scene and the scene itself, but not the entity in which it is created
	SCENE,
	// Event which is read only by the scene class
	SCENE_ONLY
};


struct Event
{
	// Base struct for the events
	Event(std::string emmitter, int type, EventDestination destination) : _type(type), _emmitter(emmitter), _destination(destination) {};

	bool operator<(const Event &e) const
	{
		return typeid(this).name() <= typeid(e).name();
	}

	bool operator==(const Event &e) const
	{
		return typeid(this).name() == typeid(e).name();
	}

	int GetType() { return _type; };

	std::string GetEmmitter() { return _emmitter; };

	EventDestination GetDestination() { return _destination; };

protected:

	int _type;
	std::string _emmitter;
	EventDestination _destination;
};
#endif
