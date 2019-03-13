#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Event.h"
#include <vector>

class EventManager
{
public:
	~EventManager();

	static EventManager* getInstance();

	void AddEvent(Event* e);
	void DeleteEvent(Event* e);

private:
	EventManager();

	static EventManager* _instance;
	std::vector<Event*> _events;
};
#endif
