#ifndef _H_RIPOEVENTS_H_
#define _H_RIPOEVENTS_H_

#include "../Engine/Events.h"

// Define the differents events types

typedef enum EventType {

	EVENT_J, EVENT_W, EVENT_A, EVENT_S, EVENT_D,
	EVENT_L_MOUSE, EVENT_MOVE_MOUSE,
	EVENT_DEATH,
	EVENT_UPDATE_TRANSFORM,
	EVENT_CHANGE_SCENE
};

// New Events specific for the game:

struct ChangeSceneEvent : Event
{
	ChangeSceneEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_CHANGE_SCENE, destination), _key(k) {}

	int _key; // number of scene
};

// Key J has been pressed
struct JEvent : Event
{
	JEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_J, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Key W has been pressed -> Player's FORWARD MOVEMENT 
struct WEvent : Event
{
	WEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_W, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Key A has been pressed -> Player's LEFT MOVEMENT 
struct AEvent : Event
{
	AEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_A, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Key s has been pressed -> Player's BACK MOVEMENT 
struct SEvent : Event
{
	SEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_S, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Key D has been pressed -> Player's RIGHT MOVEMENT
struct DEvent : Event
{
	DEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_D, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Left mouse's buttom has been pressed -> SHOT
struct L_MouseEvent : Event
{
	L_MouseEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_L_MOUSE, destination), _key(k) {}

	int _key; // this is for trying with parameters
};

// Mouse's movement-> CAMERA MOVEMENT (shooting pointer)
struct MouseMoveEvent : Event
{
	MouseMoveEvent(int x, int y, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_MOVE_MOUSE, destination), _posX(x), _posY(y) {}

	int _posX;
	int _posY;

};

// PLAYER DEATH
struct DeathEvent : Event
{
	DeathEvent(std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_DEATH, destination) {};

};


#pragma region PhysicsEvents

// Physics trnasform has been updated
struct UpdateTransformEvent : Event
{
	UpdateTransformEvent(int x, int y, float w, float h, float r, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_UPDATE_TRANSFORM, destination), _posX(x), _posY(y), _width(w), _height(h), _rotation(r) {}

	int _posX;
	int _posY;

	float _width;
	float _height;

	float _rotation;


};


#pragma endregion

#endif
