#include "TransformComponent.h"

// events from ripo
#include "RIPOEvent.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	//t = new Transform();

	SetPosition(arguments["posX"].f,
		arguments["posY"].f,
		arguments["posZ"].f);

	SetRotation(arguments["rotX"].f,
		arguments["rotY"].f,
		arguments["rotZ"].f);

	SetScale(arguments["scaleX"].f,
		arguments["sclaeY"].f,
		arguments["scaleZ"].f);

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

void TransformComponent::OnEvent(int eventType, Event e)
{
}

void TransformComponent::Update(float deltaTime)
{

}
