#include "PathFindingComponent.h"

// singleton
#include <EventManager.h>

#include "TransformComponent.h"
#include "RIPOEvent.h"

PathFindingComponent::PathFindingComponent() : Component() {}

PathFindingComponent::~PathFindingComponent() {}

void PathFindingComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	_playerX = _playerY = _playerZ = 0;
}

void PathFindingComponent::OnEvent(int eventType, Event * e) 
{
	if (eventType == EventType::EVENT_UPDATE_TRANSFORM && e->GetEmmitter() == "Player") 
	{
		// we update the position of the player so the enemies can follow
		_playerX = static_cast<UpdateTransformEvent*>(e)->_posX;
		_playerY = static_cast<UpdateTransformEvent*>(e)->_posY;
		_playerZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
	}
}

void PathFindingComponent::Update(float deltaTime) 
{
	// position of enemy and target
	TransformComponent* myPosition = static_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform"));

	// where does it have to move? and look?
	Ogre::Vector3 finalPosition(_playerX - myPosition->GetPosX(), _playerY - myPosition->GetPosY(), _playerZ - myPosition->GetPosZ());
	Ogre::Vector3 translateVector = finalPosition * Ogre::Vector3(0.1, 0.1, 0.1); // move towards player (by setting y to 0, it won't use that axis)

	/*
	// to where does it look at?
	Ogre::Vector3 initialPosition(myPosition->GetPosX(), myPosition->GetPosY(), myPosition->GetPosZ());
	Ogre::Quaternion newOrientation = initialPosition.getRotationTo(finalPosition); // new orientation of enemy

	Quat newQuat;
	newQuat.w = float(newOrientation.w);
	newQuat.x = float(newOrientation.x);
	newQuat.y = float(newOrientation.y);
	newQuat.z = float(newOrientation.z);
	
	// notify of change
	RotationEvent * RotationMovement = new RotationEvent(newQuat, _ownerEntity->GetId(), EventDestination::ENTITY);
	//EventManager::GetInstance()->NotifyObservers(RotationMovement->GetType(), RotationMovement);
	*/

	Dir newDir;
	newDir.x = translateVector.x;
	newDir.y = translateVector.z;
	newDir.z = -translateVector.y;

	// notify of change
	PhysicsMoveEvent * transformEvent = new PhysicsMoveEvent(newDir, _ownerEntity->GetId(), EventDestination::ENTITY);
	EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);
}