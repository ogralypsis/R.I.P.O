#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Event.h"
#include <vector>

class EventManager
{
public:
	~EventManager();

	EventManager* getInstance();

	void AddEvent(Event* e);
	void DeleteEvent(Event* e);

private:
	EventManager();

	EventManager* _instance;
	std::vector<Event*> _events;
};
#endif
