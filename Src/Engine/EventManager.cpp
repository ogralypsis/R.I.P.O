#include "EventManager.h"

// Static variable for the singleton
EventManager * EventManager::_instance = nullptr;

EventManager::EventManager() {}

EventManager::~EventManager()
{
	// TO DO
}

EventManager & EventManager::GetInstance()
{
	//If there is no instance... 
	if (EventManager::_instance == nullptr) {
		EventManager::_instance = new EventManager();
	}

	return *EventManager::_instance;
}

void EventManager::NotifyObservers(int eventType, const Event e)
{
	// If that event is in the dictionary,
	auto it = _observers.find(eventType);

	if (it != _observers.end())
	{
		// Notify all the observers that listen to that event
		for (auto i : it->second)
		{
			i->OnEvent(eventType, e);
		}
	}
}

void EventManager::AddObserver(int eventType, Component * observer)
{
	// Add new observer of a event	
	auto it = _observers.find( eventType);
	if (it != _observers.end()) 
	{
		it->second.emplace_back(observer);
	}
	else 
	{
		std::vector<Component*> myVector;
		myVector.emplace_back(observer);
		_observers.insert(std::pair <int, std::vector<Component*>>(eventType, myVector));
	}
}

void EventManager::RemoveObserver(int eventType, Component * observer)
{
	auto it = _observers.find(eventType);
	if (it != _observers.end())
	{
		int i = 0;
		bool found = false;
		// search for the observer
		while (!found && i < it->second.size())
		{
			// when it's found,
			if (it->second[i] == observer)
			{
				// delete the reference from the vector
				it->second.erase(it->second.begin() + i);
				// update flag
				found = true;
			}
			else
				// keep searching
				i++;
		}
	}
}

