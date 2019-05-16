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
	//Sets its id and its arguments
	_id = "PlayerController";
	_ownerEntity = e;
	std::string _mesh = arguments["mesh"]._str;

	//Initialize its booleans to false (they will be true when differents events arrived)
	_input = false;
	_moveCamera = false;
	_mustMove = false;
	_clickFlag = false;
	_shoot = false;

	_transform = nullptr;
	_render = nullptr;

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent("TransformComponent")); 
	
	_posX = _transform->GetPosX();
	_orPosX = _posX;
	_posY = _transform->GetPosY();
	_orPosY = _posY;
	_posZ = _transform->GetPosZ();
	_orPosZ = _posZ;

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("RenderComponent"));

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
			_shoot = true;
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

	if (_shoot)
	{
		Shoot();
		_shoot = false;
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

Entity* PlayerControllerComponent::BulletInstantiate()
{
	//instantiates bullet
	Entity* newEnt = Game::GetInstance().CurrentScene()->GetPrefab("Bullet");

	RenderComponent* newEntRender = dynamic_cast<RenderComponent*>(newEnt->GetComponent("RenderComponent"));
	Ogre::Vector3 _bulletPos = _render->GetNode()->getPosition() + CameraManager::GetInstance().GetGunPos();
	//newEntRender->GetNode()->translate(_bulletPos);

	Dir newDir;
	newDir.x = _bulletPos.x;
	newDir.y = _bulletPos.y;
	newDir.z = _bulletPos.z;

	// notify of change
	PhysicsMoveEvent * transformEvent = new PhysicsMoveEvent(newDir, newEnt->GetId(), EventDestination::ENTITY);
	EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);

	//std::cout << _bulletPos << std::endl;

	return newEnt;

}

void PlayerControllerComponent::Shoot()
{
	std::cout << "GONNA SHOOT" << std::endl;

	//shoots bullet
	Entity* bullet = BulletInstantiate();

	if (bullet != nullptr)
	{
		_clickFlag = true;

		ShootEvent * shootEvent = new ShootEvent(_dir, bullet->GetId(), EventDestination::ENTITY);
		EventManager::GetInstance()->NotifyObservers(shootEvent->GetType(), shootEvent);
	}
}

