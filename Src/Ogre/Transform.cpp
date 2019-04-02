#include "Transform.h"



Transform::Transform()
{
}


void Transform::SetPosition(float x, float y, float z)
{
	 _position = Ogre::Vector3(x, y, z);
}

Ogre::Vector3 Transform::GetPosition()
{
	return _position;
}

void Transform::SetRotation(float x, float y, float z)
{
	_rotation = Ogre::Vector3(x, y, z);
}

Ogre::Vector3 Transform::GetRotation()
{
	return _rotation;
}

void Transform::SetScale(float x, float y, float z)
{
	_scale = Ogre::Vector3(x, y, z); 
}

Ogre::Vector3 Transform::GetScale()
{
	return _scale;
}

Transform::~Transform()
{
}
