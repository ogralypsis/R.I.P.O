#ifndef _H_EVENTS_H_
#define _H_EVENTS_H_

#include <typeinfo>

struct Event 
{
	// Base struct for the events
	Event() {};

	bool operator<(const Event &e) const
	{
		return typeid(this).name() <= typeid(e).name();
	}

	bool operator==(const Event &e) const
	{
		return typeid(this).name() == typeid(e).name();
	}

	// Añadir emisor del evento?¿

};
#endif
