#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_

#include "Component.h"
#include <map>

class Component;

class EventManager
{
public:
	
	~EventManager();

	static EventManager & GetInstance();

	void NotifyObservers(int eventType, const Event e);
	void AddObserver(int eventType, Component* observer);
	void RemoveObserver(int eventType, Component* observer);
	

private:
	EventManager();

	static EventManager* _instance;

	std::map<int, std::vector<Component*>> _observers;

	
};
#endif
