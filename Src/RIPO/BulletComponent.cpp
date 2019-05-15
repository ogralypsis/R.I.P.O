#include "BulletComponent.h"
#include <iostream>
#include "RIPOEvent.h"


BulletComponent::BulletComponent()
{
}

void BulletComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "Bullet";

	
	_speed = arguments["speed"]._f;

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("Render"));
	//_render->GetNode()->setVisible(false);
}

void BulletComponent::OnEvent(int eventType, Event * e)
{
	//event shoot -> instantiate bullet
	if (EventType::EVENT_SHOOT == eventType)
	{
		std::cout << "Shoot" << std::endl;
	}
}

void BulletComponent::Update(float deltaTime)
{
	//std::cout << "Pos x: " << _render->GetPosition()[0] << " Pos y: " << _render->GetPosition()[1] << std::endl;

}


BulletComponent::~BulletComponent()
{
}
