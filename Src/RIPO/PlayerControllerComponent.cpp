#include "PlayerControllerComponent.h"
#include "../Engine/EntityManager.h"


//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

PlayerControllerComponent::PlayerControllerComponent(std::string id, Entity* e) : Component(id, e) {}

PlayerControllerComponent::~PlayerControllerComponent(){}


void PlayerControllerComponent::OnEvent(Event e)
{
	if ("WEvent" == typeid(e).name())
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

//TODO 

void PlayerControllerComponent::Update()
{
}

void PlayerControllerComponent::ForwardMovement()
{
}

void PlayerControllerComponent::LeftMovement()
{
}

void PlayerControllerComponent::BackMovement()
{
}

void PlayerControllerComponent::RightMovement()
{
}
