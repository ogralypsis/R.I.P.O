#ifndef _H_PLAYERCONTROLLERCOMPONENT_H_
#define _H_PLAYERCONTROLLERCOMPONENT_H_

#include <Component.h>
#include "RIPOEvent.h"
#include "TransformComponent.h"
#include "HealthComponent.h"

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent();
	~PlayerControllerComponent();

	//template<class TransformComponent>
	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event e);
	void virtual Update();


private:

	void ForwardMovement();
	void LeftMovement();
	void BackMovement();
	void RightMovement();

	void CameraMovement();

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

	//Entity* _player = nullptr;
	TransformComponent* _transform = nullptr;
	HealthComponent* _health = nullptr;
	
};

#endif