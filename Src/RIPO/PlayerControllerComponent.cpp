#include "PlayerControllerComponent.h"

// singleton
#include <EntityManager.h>

// events from ripo
#include "RIPOEvent.h"
#include "../Ogre/CameraManager.h"
//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

PlayerControllerComponent::~PlayerControllerComponent(){}

void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{

	_ownerEntity = e;

	_velocity = arguments["vel"].f;

	//_transform = _ownerEntity->GetComponent(_transform);
	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent(_transform));
	
	_posX = _transform->GetPosX();
	_orPosX = _posX;
	_posY = _transform->GetPosY();
	_orPosY = _posY;
	_posZ = _transform->GetPosZ();
	_orPosZ = _posZ;
}

void PlayerControllerComponent::OnEvent(int eventType, Event e)
{

	if ("DeathEvent" == typeid(e).name()) 
	{
		ResetPosition();
		_death = true;

	}

	else if ("WEvent" == typeid(e).name())
	{
		//ForwardMovement();
		_forward = true;
	}

	else if ("AEvent" == typeid(e).name())
	{
		//LeftMovement();
		_left = true;
	}

	else if ("SEvent" == typeid(e).name())
	{
		//BackMovement();
		_back = true;
	}

	else if ("DEvent" == typeid(e).name())
	{
		//RightMovement();
		_right = true;
	}

	else if ("MouseMoveEvent" == typeid(e).name()) 
	{
		CameraMovement();
	}
	
}

void PlayerControllerComponent::Update(float deltaTime)
{

	if (_forward) ForwardMovement(deltaTime);
	if (_forward) ForwardMovement(deltaTime);
	if (_forward) ForwardMovement(deltaTime);
	if (_forward) ForwardMovement(deltaTime);

}


void PlayerControllerComponent::ForwardMovement(float deltaTime)
{
	_posZ += _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);

}

void PlayerControllerComponent::LeftMovement(float deltaTime)
{
	_posX -= _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);
}

void PlayerControllerComponent::BackMovement(float deltaTime)
{
	_posZ -= _velocity;
	_transform->SetPosition(_posX, _posY, _posZ);
	//CameraManager::GetInstance().MoveBack();
}

void PlayerControllerComponent::RightMovement(float deltaTime)
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

	_transform->SetPosition(_posX, _posY, _posZ);
}

