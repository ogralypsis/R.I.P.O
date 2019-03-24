#include "HealthComponent.h"
#include "../Engine/EntityManager.h"

HealthComponent::HealthComponent() : Component () { }

HealthComponent::HealthComponent(std::string id, Entity* e, int health) : Component(id, e), _health(health) {}

HealthComponent::~HealthComponent() {}

void HealthComponent::OnEvent(Event e)
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
