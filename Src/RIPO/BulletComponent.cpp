#include "BulletComponent.h"
#include <iostream>
#include "RIPOEvent.h"
#include <EntityManager.h>
#include "Game.h"
#include "RigidBodyComponent.h"

BulletComponent::BulletComponent()
{
}

void BulletComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "BulletComponent";

	_speed = arguments["speed"]._f;

	_lifeTime = 10;

	_updatePhysX = false;

	_dir.x = 0; _dir.y = 0; _dir.z = 0;

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("RenderComponent"));
	//_render->GetNode()->setVisible(false);
}

void BulletComponent::OnEvent(int eventType, Event * e)
{
	//event shoot -> instantiate bullet
	if (EventType::EVENT_SHOOT == eventType)
	{
		std::cout << "SHOOT" << std::endl;
		_dir = static_cast<ShootEvent*>(e)->_dir;
		_updatePhysX = true;
	}
}

void BulletComponent::Update(float deltaTime)
{
	_lifeTime += deltaTime;

	if (_updatePhysX)
	{
		PhysicsMoveEvent * physicsMoveEvent = new PhysicsMoveEvent(_dir, _ownerEntity->GetId(), EventDestination::ENTITY);
		EventManager::GetInstance()->NotifyObservers(physicsMoveEvent->GetType(), physicsMoveEvent);
	}

	if (_lifeTime > 30)
	{
		Destroy();
	}
}


BulletComponent::~BulletComponent()
{
	if (_render != nullptr)
	{
		delete _render;
	}
}

void BulletComponent::Destroy()
{
	std::cout << "DESTROY BULLET" << std::endl;
	Game::GetInstance().CurrentScene()->DestroyEntity(_ownerEntity);
}

