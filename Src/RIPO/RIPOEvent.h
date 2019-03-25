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

// Key W has been pressed -> Player's FORWARD MOVEMENT 
struct WEvent : Event
{
	WEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};

// Key A has been pressed -> Player's LEFT MOVEMENT 
struct AEvent : Event
{
	AEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};

// Key s has been pressed -> Player's BACK MOVEMENT 
struct SEvent : Event
{
	SEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};

// Key D has been pressed -> Player's RIGHT MOVEMENT
struct DEvent : Event
{
	DEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};

// Left mouse's buttom has been pressed -> SHOT
struct L_MouseEvent : Event
{
	L_MouseEvent(int k) : _key(k) {}

	int _key; // this is for trying with parameters
};

// Mouse's movement-> CAMERA MOVEMENT (shooting pointer)
struct MouseMoveEvent : Event
{
	MouseMoveEvent(int x, int y) : _posX(x), _posY(y) {}

	int _posX;
	int _posY;

};

#endif
