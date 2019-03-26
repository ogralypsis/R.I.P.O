#ifndef _H_PLAYERCONTROLLERCOMPONENT_H_
#define _H_PLAYERCONTROLLERCOMPONENT_H_

#include <../Engine/Component.h>
#include "RIPOEvent.h"

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent();
	PlayerControllerComponent(std::string id, Entity* e, float vel, float posX, float posY, float posZ);
	~PlayerControllerComponent();

	void virtual OnEvent(Event e);

	void virtual Update();

	//Getters
	float GetNewPositionX() { return _posX; };
	float GetNewPositionY() { return _posY; };
	float GetNewPositionZ() { return _posZ; };

private:

	void ForwardMovement();
	void LeftMovement();
	void BackMovement();
	void RightMovement();

	void ResetPosition();


	//Internal variables
	float _velocity;
	float _posX;
	float _posY;
	float _posZ;

	//Original positions
	float _orPosX;
	float _orPosY;
	float _orPosZ;

	Entity* _player = nullptr;
	
};

#endif