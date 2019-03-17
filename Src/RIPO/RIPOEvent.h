#ifndef _H_RIPOEVENTS_H_
#define _H_RIPOEVENTS_H_

#include "../Engine/Events.h"
// the new Events specific for the game:

// Key J has been pressed
struct JEvent : Event
{
	JEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};
#endif
