#include "PlayerControllerComponent.h"
#include "../Engine/EntityManager.h"



//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

/*
PlayerControllerComponent::PlayerControllerComponent(std::string id, Entity* e, float vel, float posX, float posY, float posZ) : Component(id, e), 
_velocity(vel), _player(e), _posX(posX), _posY(posY), _posZ(posZ) 
{
	_orPosX = _posX;
	_orPosY = _posY;
	_orPosZ = _posZ;

}
*/

PlayerControllerComponent::~PlayerControllerComponent(){}

//template<class TransformComponent>
void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{

	_ownerEntity = e;

	_velocity = arguments["vel"].f;

	_transform = new TransformComponent();
	
	
	//_posX = _player->GetComponent<TransformComponent>(_transform)->GetPosition()._x;
	_orPosX = _posX;
	//_posY = _player->GetComponent<TransformComponent>(_transform)->GetPosition()._y;
	_orPosY = _posY;
	//_posZ = _player->GetComponent<TransformComponent>(_transform)->GetPosition()._z;
	_orPosZ = _posZ;
}

void PlayerControllerComponent::OnEvent(int eventType, Event e)
{

	if ("DeathEvent" == typeid(e).name()) 
	{
		ResetPosition();

	}

	else if ("WEvent" == typeid(e).name())
	{
		ForwardMovement();
	}

	else if ("AEvent" == typeid(e).name())
	{
		LeftMovement();
	}

	else if ("SEvent" == typeid(e).name())
	{
		BackMovement();
	}

	else if ("DEvent" == typeid(e).name())
	{
		RightMovement();
	}

	else if ("MouseMoveEvent" == typeid(e).name()) 
	{
		CameraMovement();
	}

	
}

void PlayerControllerComponent::Update()
{
}

/*float PlayerControllerComponent::GetNewPositionX()
{
	return _posX;
}

float PlayerControllerComponent::GetNewPositionY()
{
	return _posY;
}

float PlayerControllerComponent::GetNewPositionZ()
{
	return _posZ;
}*/

void PlayerControllerComponent::ForwardMovement()
{
	_posZ += _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);

}

void PlayerControllerComponent::LeftMovement()
{
	_posX -= _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);
}

void PlayerControllerComponent::BackMovement()
{
	_posZ -= _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);
}

void PlayerControllerComponent::RightMovement()
{
	_posX += _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);
}

void PlayerControllerComponent::CameraMovement()
{
	//TODO
}

void PlayerControllerComponent::ResetPosition()
{
	_posX = _orPosX;
	_posY = _orPosY;
	_posZ = _orPosZ;

}

