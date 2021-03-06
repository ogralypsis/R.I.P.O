#ifndef _H_RIPOEVENTS_H_
#define _H_RIPOEVENTS_H_

#include <Events.h>

// Define the differents events types

enum EventType {

	EVENT_J, EVENT_W, EVENT_A, EVENT_S, EVENT_D,
	EVENT_LEFT_MOUSECLICK, EVENT_MOVE_MOUSE,
	EVENT_DEATH,
	EVENT_UPDATE_TRANSFORM, EVENT_PHYSICS_MOVE,
	EVENT_CHANGE_SCENE,EVENT_ROTATION, EVENT_SHOOT
};

struct Dir {
	int x;
	int y;
	int z;
};

struct Quat {

	float w;
	float x;
	float y;
	float z;
};


// New Events specific for the game:

struct ChangeSceneEvent : Event
{
	ChangeSceneEvent(int k, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_CHANGE_SCENE, destination), _key(k) {}

	int _key; // number of scene
};

// Key J has been pressed -> for testing and simulation
struct JEvent : Event
{
	JEvent(std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_J, destination) {}
};

// Key W has been pressed -> Player's FORWARD MOVEMENT 
struct WEvent : Event
{
	WEvent(int k, Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_W, destination), _key(k), _dir(dir) {}

	int _key; // this is for trying with parameters

	// Direction to move the entity
	Dir _dir;
};

// Key A has been pressed -> Player's LEFT MOVEMENT 
struct AEvent : Event
{
	AEvent(int k, Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_A, destination), _key(k), _dir(dir) {}

	int _key; // this is for trying with parameters

	// Direction to move the entity
	Dir _dir;
};

// Key s has been pressed -> Player's BACK MOVEMENT 
struct SEvent : Event
{
	SEvent(int k, Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_S, destination), _key(k), _dir(dir) {}

	int _key; // this is for trying with parameters

	// Direction to move the entity
	Dir _dir;
};

// Key D has been pressed -> Player's RIGHT MOVEMENT
struct DEvent : Event
{
	DEvent(int k, Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_D, destination), _key(k), _dir(dir) {}

	int _key; // this is for trying with parameters

			  // Direction to move the entity
	Dir _dir;
};

// Left mouse's buttom has been pressed -> SHOT
struct L_MouseEvent : Event
{
	L_MouseEvent(std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_LEFT_MOUSECLICK, destination){}
};

// Mouse's movement-> CAMERA MOVEMENT (shooting pointer)
struct MouseMoveEvent : Event
{
	MouseMoveEvent(int x, int y, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_MOVE_MOUSE, destination), _posX(x), _posY(y) {}

	int _posX;
	int _posY;
};

// Event for telling the rigidbody to update it's orientation
struct RotationEvent : Event
{
	RotationEvent(Quat q, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_ROTATION, destination), _quat(q) {}

	Quat _quat;
};

// PLAYER DEATH
struct DeathEvent : Event
{
	DeathEvent(std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_DEATH, destination) {};

};


#pragma region PhysicsEvents

// Physics transform has been updated
struct UpdateTransformEvent : Event
{
	UpdateTransformEvent(float x, float y, float z, float r, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_UPDATE_TRANSFORM, destination), _posX(x), _posY(y), _posZ(z), _rotation(r) {}

	float _posX;
	float _posY;
	float _posZ;

	float _rotation;


};

// A physics movement has occured

struct PhysicsMoveEvent : Event
{
	PhysicsMoveEvent(Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_PHYSICS_MOVE, destination), _dir(dir) {}

	Dir _dir;
};

struct ShootEvent : Event
{
	ShootEvent(Dir dir, std::string emmiter, EventDestination destination) : Event(emmiter, EventType::EVENT_SHOOT, destination), _dir(dir) {};
	
	// Direction to move the entity
	Dir _dir;
};

#pragma endregion

#endif
