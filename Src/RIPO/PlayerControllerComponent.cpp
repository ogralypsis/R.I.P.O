#include "PlayerControllerComponent.h"

// singleton
#include <EntityManager.h>
#include <EventManager.h>
#include <CameraManager.h>

// events from ripo
#include "RIPOEvent.h"

//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

PlayerControllerComponent::~PlayerControllerComponent(){}

void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{

	_ownerEntity = e;
	_id = "PlayerController";

	_velocity = arguments["vel"]._f;

	_input = false;
	_mustMove = false;

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform")); 
	
	_posX = _transform->GetPosX();
	_orPosX = _posX;
	_posY = _transform->GetPosY();
	_orPosY = _posY;
	_posZ = _transform->GetPosZ();
	_orPosZ = _posZ;

	//RenderComponent* render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("Render"));

	//CameraManager::GetInstance().AttachPlayer(render->GetNode());
}

void PlayerControllerComponent::OnEvent(int eventType, Event * e)
{

	if (EventType::EVENT_DEATH == eventType) 
	{
		ResetPosition();
		_death = true;
	}

	else if (EventType::EVENT_W == eventType)
	{
		_input = true;
		_dir = static_cast<WEvent*>(e)->_dir;

	}

	else if (EventType::EVENT_A == eventType)
	{
		_input = true;
		_dir = static_cast<AEvent*>(e)->_dir;

	}

	else if (EventType::EVENT_S == eventType)
	{
		_input = true;
		_dir = static_cast<SEvent*>(e)->_dir;

	}

	else if (EventType::EVENT_D == eventType)
	{
		_input = true;
		_dir = static_cast<DEvent*>(e)->_dir;
	
	}

	else if (EventType::EVENT_MOVE_MOUSE == eventType)
	{		
		_mouseX = static_cast<MouseMoveEvent*>(e)->_posX;
		_mouseY = static_cast<MouseMoveEvent*>(e)->_posY;
		_moveCamera = true;		
	}

	else if (eventType == EventType::EVENT_UPDATE_TRANSFORM)
	{
		_mustMove = true;
		_posX = static_cast<UpdateTransformEvent*>(e)->_posX;
		_posY = static_cast<UpdateTransformEvent*>(e)->_posY;
		_posZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
	}

	if (_input) {
		PhysicsMoveEvent * physicsMoveEvent = new PhysicsMoveEvent(_dir, _ownerEntity->GetId(), EventDestination::ENTITY);
		EventManager::GetInstance()->NotifyObservers(physicsMoveEvent->GetType(), physicsMoveEvent);
		_input = false;
	}
	
}

void PlayerControllerComponent::Update(float deltaTime)
{
	if (_mustMove)
		CameraMovement();
	if(_moveCamera) 
		CameraRotation(deltaTime);
}


void PlayerControllerComponent::ForwardMovement(float deltaTime)
{


}

void PlayerControllerComponent::LeftMovement(float deltaTime)
{

}

void PlayerControllerComponent::BackMovement(float deltaTime)
{

}

void PlayerControllerComponent::RightMovement(float deltaTime)
{

}

void PlayerControllerComponent::CameraMovement()
{
	_mustMove = false;
	CameraManager::GetInstance().CameraMove({ _posX, _posZ + 10, _posY + 5 });
}

void PlayerControllerComponent::CameraRotation(float deltaTime)
{
	CameraManager::GetInstance().FPSrotation(deltaTime, _mouseX, _mouseY);
	_moveCamera = false;

}

void PlayerControllerComponent::ResetPosition()
{
	_posX = _orPosX;
	_posY = _orPosY;
	_posZ = _orPosZ;

	_transform->SetPosition(_posX, _posY, _posZ);
}

