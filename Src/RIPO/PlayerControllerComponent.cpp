#include "PlayerControllerComponent.h"

// singleton
#include <EntityManager.h>
#include <EventManager.h>
#include <CameraManager.h>

#include <iostream>

// events from ripo
#include "RIPOEvent.h"

#include "Game.h"

//Constructors
PlayerControllerComponent::PlayerControllerComponent() : Component() { }

PlayerControllerComponent::~PlayerControllerComponent(){

	if (_transform) {
		_transform = nullptr;
		delete _transform;
	}
	if (_render) {
		_render = nullptr;
		delete _render;
	}
}

void PlayerControllerComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{

	_ownerEntity = e;
	_id = "PlayerController";

	std::string _mesh = arguments["mesh"]._str;

	_velocity = arguments["vel"]._f;

	_input = false;
	_mustMove = false;

	_transform = nullptr;
	_render = nullptr;

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform")); 
	
	_posX = _transform->GetPosX();
	_orPosX = _posX;
	_posY = _transform->GetPosY();
	_orPosY = _posY;
	_posZ = _transform->GetPosZ();
	_orPosZ = _posZ;

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("Render"));

	CameraManager::GetInstance().AttachPlayer(_mesh, _render->GetNode());
}

void PlayerControllerComponent::OnEvent(int eventType, Event * e)
{

	if (EventType::EVENT_DEATH == eventType) 
	{

		// upon the death of the player, the game changes back to the main menu
		Game::GetInstance().QueueScene("0");

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

		/*_rotX = CameraManager::GetInstance().GetRotX();
		_rotY = CameraManager::GetInstance().GetRotY();*/
	}
	else if (EventType::EVENT_LEFT_MOUSECLICK == eventType)
	{
		
		if (!_clickFlag)
		{
			std::cout << "GONNA SHOOT" << std::endl;

			//shoots bullet
			BulletInstantiate();

			ShootEvent * shootEvent = new ShootEvent(_ownerEntity->GetId(), EventDestination::SCENE);
			EventManager::GetInstance()->NotifyObservers(shootEvent->GetType(), shootEvent);

			_clickFlag = true;
			_clickFlagTimer = 0;
		}
	}

	else if (eventType == EventType::EVENT_UPDATE_TRANSFORM && e->GetEmmitter() == _ownerEntity->GetId())
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
	if(_moveCamera) 
		CameraRotation(deltaTime);


	if (_clickFlag)
	{
		_clickFlagTimer += deltaTime;
		if (_clickFlagTimer > 5)
			_clickFlag = false;
	}
}




void PlayerControllerComponent::CameraRotation(float deltaTime)
{
			
	Ogre::Quaternion q =  CameraManager::GetInstance().FPSrotation(deltaTime, _mouseX, _mouseY);

	Quat newQuat;
	newQuat.w = float(q.w);
	newQuat.x = float(q.x);
	newQuat.y = float(q.y);
	newQuat.z = float(q.z);

	RotationEvent * RotationMovement = new RotationEvent(newQuat, _ownerEntity->GetId(), EventDestination::ENTITY);
	EventManager::GetInstance()->NotifyObservers(RotationMovement->GetType(), RotationMovement);

	_moveCamera = false;

}

void PlayerControllerComponent::ResetPosition()
{
	_posX = _orPosX;
	_posY = _orPosY;
	_posZ = _orPosZ;

	_transform->SetPosition(_posX, _posY, _posZ);
}

void PlayerControllerComponent::BulletInstantiate()
{
	//instantiates bullet
	Entity* newEnt = Game::GetInstance().CurrentScene()->GetPrefab("Bullet");

	RenderComponent* newEntRender = dynamic_cast<RenderComponent*>(newEnt->GetComponent("Render"));
	newEntRender->GetNode()->_setDerivedPosition(_render->GetNode()->getPosition());

}

