#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Event.h"
#include <vector>

class EventManager
{
public:
	EventManager();
	~EventManager();

	void AddEvent(Event* e);
	void DeleteEvent(Event* e);

private:
	std::vector<Event*> _events;
};
#endif
