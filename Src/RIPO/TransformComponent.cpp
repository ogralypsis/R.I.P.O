#include "TransformComponent.h"



TransformComponent::TransformComponent()
{

	t = new Transform();

}

TransformComponent::TransformComponent(std::string arg)
{
}

TransformComponent::TransformComponent(std::string id, Entity * e)
{
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	_pos._x = x;
	_pos._y = y;
	_pos._z = z;
	t->SetPosition(x, y, z);
}

void TransformComponent::SetRotation(float x, float y, float z)
{

	_rot._x = x;
	_rot._y = y;
	_rot._z = z;
	t->SetRotation(x, y, z);
}

void TransformComponent::SetScale(float x, float y, float z)
{

	_scale._x = x;
	_scale._y = y;
	_scale._z = z;
	t->SetScale(x, y, z);
}

void TransformComponent::OnEvent(Event e)
{
}

void TransformComponent::Update()
{
}
