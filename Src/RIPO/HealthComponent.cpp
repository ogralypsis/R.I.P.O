#include "HealthComponent.h"

// singleston
#include <EntityManager.h>

// events from ripo
#include "RIPOEvent.h"


HealthComponent::HealthComponent() : Component () { }

HealthComponent::~HealthComponent() {}

void HealthComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
}

void HealthComponent::OnEvent(int eventType, Event e)
{
	if ("JEvent" == typeid(e).name())
	{
		DecreaseHealth();
	}
}

void HealthComponent::Update()
{
}

void HealthComponent::DecreaseHealth()
{
	_health -= 5;
	CheckHealth();
}

void HealthComponent::CheckHealth()
{
	if (_health <= 0) 
	{
		EntityManager::getInstance()->DeleteEntity(_ownerEntity);
	}
}
