#ifndef _H_SUBJECT_H_
#define _H_SUBJECT_H_

#include "Observer.h"
#include <vector>
class Subject
{
public:
	// Register an observer
	virtual void AddObserver(Observer* o);

	// Unregister an observer
	virtual void RemoveObserver(Observer* o);

	// Notify all observers
	virtual void NotifyObservers(Event* e);

	// Clear list
	virtual void Clear();

protected:
	std::vector<Observer*> _observers;
};
#endif
