#include "HealthComponent.h"

// singleston
#include <EventManager.h>

// events from ripo
#include "RIPOEvent.h"

HealthComponent::HealthComponent() : Component () { }

HealthComponent::~HealthComponent() {}

void HealthComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "HealthComponent";
	_health = arguments["health"]._i;
}

void HealthComponent::OnEvent(int eventType, Event * e)
{
	if (eventType == EventType::EVENT_J)
	{
		DecreaseHealth();
	}
}

void HealthComponent::Update(float deltaTime) 
{
	// TO DO: RESTORE SOME HEALTH WITH TIME
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
		DeathEvent * deathEvent = new DeathEvent(_ownerEntity->GetId(), EventDestination::ENTITY);
		EventManager::GetInstance()->NotifyObservers(deathEvent->GetType(), deathEvent);
	}
}
