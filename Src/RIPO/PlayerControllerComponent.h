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

	//template<class TransformComponent>
	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);


private:

	void ForwardMovement(float deltaTime);
	void LeftMovement(float deltaTime);
	void BackMovement(float deltaTime);
	void RightMovement(float deltaTime);

	void CameraMovement();
	void CameraRotation(float deltaTime);


	void ResetPosition();


	//Internal variables
	float _velocity;
	float _posX;
	float _posY;
	float _posZ;

	Dir _dir;

	//Original positions
	float _orPosX;
	float _orPosY;
	float _orPosZ;

	//Booleans to activate the different directions
	bool _input;
	bool _death = false;
	bool _moveCamera = false;
	bool _mustMove;

	//Mouse coords
	Ogre::Real _mouseX;
	Ogre::Real _mouseY;

	//Entity* _player = nullptr;
	TransformComponent* _transform = nullptr;
	
};

#endif