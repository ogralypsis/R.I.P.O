#include "EventManager.h"

// Static variable for the singleton
EventManager * EventManager::_instance = nullptr;

EventManager::EventManager() {}

EventManager::~EventManager()
{
	// TO DO
}

EventManager * EventManager::GetInstance()
{
	//If there is no instance... 
	if (_instance == nullptr) {
		_instance = new EventManager();
	}

	return _instance;
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
			// MiRAR SI DESTINO ES ENTIDAD 
			// COGER EL EMISOR DEL MENSAJE Y COMPROBARLO CON LA ENTIDAD PROPIETARIA DEL COMPONENTE
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