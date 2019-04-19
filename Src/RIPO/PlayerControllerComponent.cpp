#include "PlayerControllerComponent.h"
#include "../Engine/EntityManager.h"



//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

PlayerControllerComponent::~PlayerControllerComponent(){}

//template<class TransformComponent>
void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{

	_ownerEntity = e;

	_velocity = arguments["vel"].f;

	_transform = new TransformComponent();
	//_transform = _player->GetComponent<TransformComponent>(_transform);
	
	
	_posX = _transform->GetPosition()._x;
	_orPosX = _posX;
	_posY = _transform->GetPosition()._y;
	_orPosY = _posY;
	_posZ = _transform->GetPosition()._z;
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

	_transform->SetPosition(_posX, _posY, _posZ);
}

