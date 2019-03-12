#include "Subject.h"

// Register an observer
void Subject::AddObserver(Observer * o)
{
	_observers.emplace_back(o);
}

// Unregister an observer
void Subject::RemoveObserver(Observer * o)
{
	int i = 0;
	bool found = false;
	// search for the observer o
	while (!found && i < _observers.size())
	{
		// when it's found,
		if (_observers.at(i) == o)
		{
			Observer* aux = _observers.at(i);
			// delete the reference from the vector
			_observers.erase(_observers.begin() + i);
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

// Notify all observers
void Subject::NotifyObservers(Event* e)
{
	for (auto o : _observers)
		o->OnEvent(e);
}

void Subject::Clear()
{
	// delete each pointer
	for (std::vector<Observer *>::iterator it = _observers.begin(); it != _observers.end(); ++it)
		delete (*it);
	// clear the vector
	_observers.clear();
}
