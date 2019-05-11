#ifndef _H_EVENTMANAGER_H_
#define _H_EVENTMANAGER_H_
///<summary>
/// Container of events. Manages all entities. Prepared to be singleton
///</summary>

#include "Component.h"
#include <map>

class Component;

class EventManager
{
public:
	~EventManager();

	///<summary>
	/// Gets the instance of the singleton so it there's only one manager
	///</summary>
	static EventManager* GetInstance();

	///<summary>
	/// calls function OnEvent of all components subscribed to event of type eventType
	///</summary>
	///<param name="eventType"> type of the event </param>
	///<param name="e"> event that has happened </param>
	void NotifyObservers(int eventType, Event * e);

	///<summary>
	/// subscribes a component to an event so it gets notified when event happens
	///</summary>
	///<param name="eventType"> type of the event </param>
	///<param name="observer"> components that has to be subscribed to event of type eventType </param>
	void AddObserver(int eventType, Component* observer);

	///<summary>
	/// unsubscribes a component to an event so it stops getting notified when event happens
	///</summary>
	///<param name="eventType"> type of the event </param>
	///<param name="observer"> components that has to be unsubscribed to event of type eventType </param>
	void RemoveObserver(int eventType, Component* observer);

	///<summary>
	/// stores the listeners into the map of the singleton
	///</summary>
	///<param name="observers"> map of (event + component that listen to that event) </param>
	void SetJsonObservers(const std::map<std::string, std::vector<Component*>> observers);

	///<summary>
	/// Returns the map of listeners (event + component that listen to that event)
	///</summary>
	std::map<std::string, std::vector<Component*>> GetObservers();


private:
	///<summary>
	/// constructor is private so it can't be called (only called from GetInstance)
	///</summary>
	EventManager();

	///<summary>
	/// Deletes all observers from the map
	///</summary>
	void ClearObservers();

	///<summary>
	/// instance of singleton
	///</summary>
	static EventManager* _instance;

	///<summary>
	/// map of listeners (event + component that listen to that event)
	///</summary>
	std::map<int, std::vector<Component*>> _observers;

	///<summary>
	/// map of listeners (event + component that listen to that event)
	///</summary>
	std::map<std::string, std::vector<Component*>> _observersJSON;
};
#endif
