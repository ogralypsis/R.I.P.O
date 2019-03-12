#ifndef _H_OBSERVER_H_
#define _H_OBSERVER_H_

#include "Event.h"
class Observer
{
public:
	virtual void OnEvent(Event* e) = 0;
};
#endif
