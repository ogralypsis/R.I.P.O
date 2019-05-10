#include "TransformComponent.h"

// events from ripo
#include "RIPOEvent.h"

#include <EventManager.h>

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "Transform";

	_mustMove = false;

	SetPosition(arguments["posX"]._f,
		arguments["posY"]._f,
		arguments["posZ"]._f);

	SetRotation(arguments["rotX"]._f,
		arguments["rotY"]._f,
		arguments["rotZ"]._f);

	SetScale(arguments["scaleX"]._f,
		arguments["scaleY"]._f,
		arguments["scaleZ"]._f);

}

void TransformComponent::SetPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
}

float TransformComponent::GetPosX()
{
	return _pos.x;
}

float TransformComponent::GetPosY()
{
	return _pos.y;
}

float TransformComponent::GetPosZ()
{
	return _pos.z;
}

void TransformComponent::SetRotation(float x, float y, float z)
{
	_rot.x = x;
	_rot.y = y;
	_rot.z = z;
}

float TransformComponent::GetRotX()
{
	return _rot.x;
}

float TransformComponent::GetRotY()
{
	return _rot.y;
}

float TransformComponent::GetRotZ()
{
	return _rot.z;
}

void TransformComponent::SetScale(float x, float y, float z)
{

	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}

float TransformComponent::GetScaleX()
{
	return _scale.x;
}

float TransformComponent::GetScaleY()
{
	return _scale.y;
}

float TransformComponent::GetScaleZ()
{
	return _scale.z;
}

void TransformComponent::OnEvent(int eventType, Event * e)
{
	if (_ownerEntity->GetId() == e->GetEmmitter()) {
		if (eventType == EventType::EVENT_PHYSICS_MOVE) {
			_mustMove = true;
			_auxPosX = static_cast<PhysicsMoveEvent*>(e)->_posX;
			_auxPosY = static_cast<PhysicsMoveEvent*>(e)->_posY;
			_auxPosZ = static_cast<PhysicsMoveEvent*>(e)->_posZ;
			// se tiene que actualizar las posiciones en el update segun lo que le llega del evento

			UpdateTransformEvent * utEvent = new UpdateTransformEvent(_auxPosX, _auxPosY, _auxPosZ, 0, _ownerEntity->GetId(), EventDestination::ENTITY);
			EventManager::GetInstance()->NotifyObservers(utEvent->GetType(), utEvent);
		}
	}
}

void TransformComponent::Update(float deltaTime)
{
	if (_mustMove) {
		SetPosition(_auxPosX, _auxPosY, _auxPosZ);
	}
}
