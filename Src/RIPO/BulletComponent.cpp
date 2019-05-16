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

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("RenderComponent"));
	//_render->GetNode()->setVisible(false);
}

void BulletComponent::OnEvent(int eventType, Event * e)
{
	//event shoot -> instantiate bullet
	if (EventType::EVENT_SHOOT == eventType)
	{
		std::cout << "SHOOT" << std::endl;
	}
}

void BulletComponent::Update(float deltaTime)
{
	_lifeTime += deltaTime;

	if (_lifeTime > 20)
		Destroy();
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

