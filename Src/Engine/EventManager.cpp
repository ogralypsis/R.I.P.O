#include "EventManager.h"

EventManager::EventManager()
{

}

void EventManager::AddEvent(Event e)
{
	_events.push_back(e);
}

EventManager::~EventManager()
{

}