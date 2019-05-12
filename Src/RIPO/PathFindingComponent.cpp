#include "PathFindingComponent.h"
#include <EntityManager.h>
#include <EventManager.h>
#include <iostream>

PathFindingComponent::PathFindingComponent() : Component() {}

PathFindingComponent::~PathFindingComponent() {}

void PathFindingComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	_playerX = _playerY = _playerZ = 0;

	_negativeDir.x = _negativeDir.y = _negativeDir.z = 0;
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
	Dir newDir;

	// Set force to 0 (temporal maybe?)
	PhysicsMoveEvent * transformEvent = new PhysicsMoveEvent(_negativeDir, _ownerEntity->GetId(), EventDestination::ENTITY);
	EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);

	// where does it have to move? and look?
	Ogre::Vector3 initialOrientation(0, 0, 0);
	Ogre::Vector3 finalOrientation(_playerX - myPosition->GetPosX(), _playerY - myPosition->GetPosY(), _playerZ - myPosition->GetPosZ());
	Ogre::Quaternion newOrientation = initialOrientation.getRotationTo(finalOrientation); // new orientation of enemy
	Ogre::Vector3 translateVector = finalOrientation * Ogre::Vector3(myPosition->GetPosX(), myPosition->GetPosY(), myPosition->GetPosZ()); // move towards player

	newDir.x = translateVector.x + myPosition->GetPosX();
	newDir.y = translateVector.y + myPosition->GetPosY();
	newDir.z = translateVector.z + myPosition->GetPosZ();
	_negativeDir.x = -newDir.x;
	_negativeDir.y = -newDir.y;
	_negativeDir.z = -newDir.z;

	_actualTranslateVect = translateVector; 
		
	std::cout << "POS Y RENDER : " + _ownerEntity->GetId() + " " << myPosition->GetPosX() + newDir.x << std::endl;
	std::cout << "POS Z RENDER : " + _ownerEntity->GetId() + " " << myPosition->GetPosZ() + newDir.z << std::endl;
	// notify of change
	transformEvent = new PhysicsMoveEvent(newDir, _ownerEntity->GetId(), EventDestination::ENTITY);
	EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);

}