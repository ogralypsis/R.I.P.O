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
	// TODO: TENDRIA QUE HACERSE POR EVENTOS...LA POS DEL PLAYER LE LLEGA POR EVENTO QUE ENVIA EL PROPIO PLAYER	
	// position of enemy and target
	TransformComponent* myPosition = static_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform"));

	// where does it have to move? and look?
	Ogre::Vector3 initialOrientation(0, 0, 1);
	Ogre::Vector3 finalOrientation(_playerX - myPosition->GetPosX(), _playerY - myPosition->GetPosY(), _playerZ - myPosition->GetPosZ());
	Ogre::Quaternion newOrientation = initialOrientation.getRotationTo(finalOrientation); // new orientation of enemy
	Ogre::Vector3 translateVector = newOrientation * Ogre::Vector3(0, 0, 0.1); // move towards player
	
	Dir newDir;
	newDir.x = translateVector.x + myPosition->GetPosX();
	newDir.y = translateVector.y + myPosition->GetPosY();
	newDir.z = translateVector.z + myPosition->GetPosZ();

	// notify of change
	//PhysicsMoveEvent * transformEvent = new PhysicsMoveEvent(newDir, _ownerEntity->GetId(), EventDestination::SCENE);
	//EventManager::GetInstance()->NotifyObservers(transformEvent->GetType(), transformEvent);	
}
