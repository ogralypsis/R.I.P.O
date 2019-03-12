#include "EventManager.h"

EventManager::EventManager() {}

EventManager::~EventManager()
{
	// delete each pointer
	for (std::vector<Event*>::iterator it = _events.begin(); it != _events.end(); ++it)
		delete (*it);
	// clear the vector
	_events.clear();
}

void EventManager::AddEvent(Event* e)
{
	_events.push_back(e);
}

void EventManager::DeleteEvent(Event * e)
{
	int i = 0;
	bool found = false;
	// search for the event e
	while (!found && i < _events.size())
	{
		// when it's found,
		if (_events.at(i) == e)
		{
			Event* aux = _events.at(i);
			// delete the reference from the vector
			_events.erase(_events.begin() + i);
			// delete the pointer
			delete aux;
			// update flag
			found = true;
		}
		else
			// keep searching
			i++;
	}
}
