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


void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
}

void PlayerControllerComponent::OnEvent(Event e)
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

	
}

void PlayerControllerComponent::Update()
{
}

void PlayerControllerComponent::ForwardMovement()
{
	_posZ += _velocity;

}

void PlayerControllerComponent::LeftMovement()
{
	_posX -= _velocity;
}

void PlayerControllerComponent::BackMovement()
{
	_posZ -= _velocity;
}

void PlayerControllerComponent::RightMovement()
{
	_posX += _velocity;
}

void PlayerControllerComponent::ResetPosition()
{
	_posX = _orPosX;
	_posY = _orPosY;
	_posZ = _orPosZ;

}

