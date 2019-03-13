#include "Event.h"
#include "EventManager.h"

Event::Event() 
{
	EventManager* manager = EventManager::getInstance();
	manager->AddEvent(this);
}

Event::~Event() {}