#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Event.h"
#include <vector>
using namespace std;
class EventManager
{
public:
	EventManager();
	~EventManager();
	void AddEvent(Event e);

protected:
	vector<Event> _events;
};

#endif
