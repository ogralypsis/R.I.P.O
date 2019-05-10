#include "PathFindingComponent.h"
#include <MyOgre.h>
#include <EntityManager.h>
#include <EventManager.h>
#include "TransformComponent.h"
#include "RIPOEvent.h"

PathFindingComponent::PathFindingComponent() : Component() {}

PathFindingComponent::~PathFindingComponent() {}

void PathFindingComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
}

void PathFindingComponent::OnEvent(int eventType, Event * e) {}

void PathFindingComponent::Update(float deltaTime) 
{
	// position of enemy and target
	TransformComponent* playerPosition = static_cast<TransformComponent*>(EntityManager::getInstance()->GetEntityByName("Player")->GetComponent("Transform"));
	TransformComponent* myPosition = static_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform"));

	// where does it have to move? and look?
	Ogre::Vector3 initialOrientation(0, 0, 1);
	Ogre::Vector3 finalOrientation(playerPosition->GetPosX() - myPosition->GetPosX(), playerPosition->GetPosY() - myPosition->GetPosY(), playerPosition->GetPosZ() - myPosition->GetPosZ());
	Ogre::Quaternion newOrientation = initialOrientation.getRotationTo(finalOrientation); // new orientation of enemy
	Ogre::Vector3 translateVector = newOrientation * Ogre::Vector3(0, 0, 0.1); // move towards player
	
	PhysicsMoveEvent * transformEvent = new PhysicsMoveEvent(translateVector.x + myPosition->GetPosX(),
		translateVector.y + myPosition->GetPosY(), translateVector.z + myPosition->GetPosZ(), _ownerEntity->GetId(), EventDestination::SCENE);
	EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);
}
