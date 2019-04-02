#ifndef _TRANSFORM_H
#define _TRNASFORM_H

#include <OgreVector3.h>

class Transform
{
public:
	Transform();

	
	
	//Position
	void SetPosition(float x, float y, float z);
	Ogre::Vector3 GetPosition();

	//Rotation
	void SetRotation(float x, float y, float z);
	Ogre::Vector3 GetRotation();

	//Scale
	void SetScale(float x, float y, float z);
	Ogre::Vector3 GetScale();

	~Transform();

private:

	Ogre::Vector3 _position;
	Ogre::Vector3 _rotation;
	Ogre::Vector3 _scale;
};

#endif

