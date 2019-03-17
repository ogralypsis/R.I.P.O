#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Component.h"
#include "Events.h"
#include <map>

class EventManager
{
public:
	
	~EventManager();

	static EventManager* getInstance();

	void NotifyObservers(Event e);
	void AddObserver(Event e, Component* observer);
	void RemoveObserver(Event e, Component* observer);

private:
	EventManager();

	static EventManager* _instance;

	std::map<Event, std::vector<Component*>> _observers;
};
#endif
