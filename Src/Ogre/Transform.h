#ifndef _TRANSFORM_H
#define _TRNASFORM_H

#include <OgreVector3.h>

class Transform
{
public:
	Transform();

	Ogre::Vector3 GetPosition() { return _position; };
	//sceneNode????
	void SetPosition(float x, float y, float z) { _position = Ogre::Vector3(x, y, z); };
	void SetRotation(float x, float y, float z) { _rotation = Ogre::Vector3(x, y, z); };
	void SetScale(float x, float y, float z) { _scale = Ogre::Vector3(x, y, z); };
	~Transform();

private:

	Ogre::Vector3 _position;
	Ogre::Vector3 _rotation;
	Ogre::Vector3 _scale;
};

#endif

