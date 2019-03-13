#include "HealthComponent.h"
#include "DeathEvent.h"

HealthComponent::HealthComponent(std::string id, Entity* e, int health) : Component(id, e), _health(health) {}

HealthComponent::~HealthComponent() {}

void HealthComponent::OnEvent()
{
	DecreaseHealth();
}

void HealthComponent::DecreaseHealth()
{
	_health -= 5;
}

void HealthComponent::CheckHealth()
{
	if (_health <= 0) 
	{
		Event* event = new DeathEvent();
	}
}
