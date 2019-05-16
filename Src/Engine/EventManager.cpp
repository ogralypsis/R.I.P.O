#include "EventManager.h"

// Static variable for the singleton
EventManager * EventManager::_instance = nullptr;

EventManager::EventManager() {}

EventManager::~EventManager()
{
	ClearObservers();
}

EventManager * EventManager::GetInstance()
{
	//If there is no instance
	if (_instance == nullptr) {
		_instance = new EventManager();
	}

	return _instance;
}

void EventManager::ClearObservers()
{
	// Iterate all the map
	for (std::map<int, std::vector<Component*>>::iterator it = _observers.begin(); it != _observers.end(); ++it) {
		// Iterate vector 
		for (std::vector<Component *>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {
			(*it2) = nullptr;
			delete (*it2);
		}
		(*it).second.clear();
	}

	_observers.clear();

	// Iterate all the map
	for (std::map<std::string, std::vector<Component*>>::iterator Jsonit = _observersJSON.begin(); Jsonit != _observersJSON.end(); ++Jsonit) {
		// Iterate vector
		for (std::vector<Component *>::iterator it3 = (*Jsonit).second.begin(); it3 != (*Jsonit).second.end(); ++it3) {
			(*it3) = nullptr;
			delete (*it3);
		}
		(*Jsonit).second.clear();
	}

	_observersJSON.clear();
}


void EventManager::NotifyObservers(int eventType, Event * e)
{	
	// If that event is in the dictionary,
	auto it = _observers.find(eventType);

	if (it != _observers.end())
	{
		// Notify all the observers that listen to that event
		for (auto i : it->second)
		{
			// check if destiny is entity
			// take emmiter and check if it's the entity owner of component
			if (e->GetDestination() == EventDestination::ENTITY) {
				if(i->GetOwnerEntId() == e->GetEmmitter())
					i->OnEvent(eventType, e);
			}
			else if(e->GetDestination() == EventDestination::SCENE)

				i->OnEvent(eventType, e);
		}
	}
}

void EventManager::AddObserver(int eventType, Component * observer)
{
	// Add new observer of a event	
	auto it = _observers.find(eventType);
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
		size_t i = 0;
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
void EventManager::SetJsonObservers(const std::map<std::string, std::vector<Component*>> observers)
{
	_observersJSON = observers;
}

std::map<std::string, std::vector<Component*>> EventManager::GetObservers()
{
	return _observersJSON;
}
