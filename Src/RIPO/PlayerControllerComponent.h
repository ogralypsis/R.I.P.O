#ifndef _H_PLAYERCONTROLLERCOMPONENT_H_
#define _H_PLAYERCONTROLLERCOMPONENT_H_

#include <Component.h>
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "RenderComponent.h"

// events from ripo
#include "RIPOEvent.h"

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent();
	~PlayerControllerComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);


private:

	// Updates the rotation in camera
	void CameraRotation(float deltaTime);

	//Sets player in initial position
	void ResetPosition();

	//Instantiates a bullet entity for the player to shoot
	Entity* BulletInstantiate();

	//Create the shootEvent
	void Shoot();

	//Internal variables
	float _posX;
	float _posY;
	float _posZ;

	float _rotX;
	float _rotY;

	std::string _mesh = "";

	//variables to control shooting frequency
	bool _clickFlag;
	bool _shoot;
	float _clickFlagTimer;

	Dir _dir;

	//Original positions
	float _orPosX;
	float _orPosY;
	float _orPosZ;

	//Booleans to activate the different directions
	bool _input;
	bool _moveCamera;
	bool _mustMove;

	//Mouse coords
	Ogre::Real _mouseX;
	Ogre::Real _mouseY;

	TransformComponent* _transform;
	RenderComponent* _render;
	
};

#endif