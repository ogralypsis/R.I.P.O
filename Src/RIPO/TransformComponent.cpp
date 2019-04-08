#include "TransformComponent.h"



TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	t = new Transform();

	SetPosition(_pos._x = arguments["posX"].f,
		_pos._y = arguments["posY"].f,
		_pos._z = arguments["posZ"].f);

	SetRotation(_rot._x = arguments["rotX"].f,
		_rot._y = arguments["rotY"].f,
		_rot._z = arguments["rotZ"].f);

	SetScale(_scale._x = arguments["scaleX"].f,
		_scale._y = arguments["sclaeY"].f,
		_scale._z = arguments["scaleZ"].f);

}

void TransformComponent::SetPosition(float x, float y, float z)
{
	_pos._x = x;
	_pos._y = y;
	_pos._z = z;
	t->SetPosition(x, y, z);
}

position TransformComponent::GetPosition()
{
	return _pos;
}

void TransformComponent::SetRotation(float x, float y, float z)
{

	_rot._x = x;
	_rot._y = y;
	_rot._z = z;
	t->SetRotation(x, y, z);
}

rotation TransformComponent::GetRotation()
{
	return _rot;
}

void TransformComponent::SetScale(float x, float y, float z)
{

	_scale._x = x;
	_scale._y = y;
	_scale._z = z;
	t->SetScale(x, y, z);
}

scale TransformComponent::GetScale()
{
	return _scale;
}

void TransformComponent::OnEvent(int eventType, Event e)
{
}

void TransformComponent::Update()
{
}
