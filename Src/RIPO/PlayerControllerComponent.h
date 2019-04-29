#ifndef _H_PLAYERCONTROLLERCOMPONENT_H_
#define _H_PLAYERCONTROLLERCOMPONENT_H_

#include <Component.h>
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
	void virtual Update(float deltaTime);


private:

	void ForwardMovement(float deltaTime);
	void LeftMovement(float deltaTime);
	void BackMovement(float deltaTime);
	void RightMovement(float deltaTime);

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

	//Booleans to activate the different directions
	bool _forward = false;
	bool _back = false;
	bool _right = false;
	bool _left = false;
	bool _death = false;

	//Entity* _player = nullptr;
	TransformComponent* _transform = nullptr;
	
};

#endif