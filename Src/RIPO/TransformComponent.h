#ifndef _H_TRANSFORMCOMPONENT_H_
#define _H_TRANSFORMCOMPONENT_H_

#include <Component.h>
#include <Transform.h>

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	//Position
	void SetPosition(float x, float y, float z);
	float GetPosX();
	float GetPosY();
	float GetPosZ();

	//Rotation
	void SetRotation(float x, float y, float z);
	float GetRotX();
	float GetRotY();
	float GetRotZ();

	//Scale
	void SetScale(float x, float y, float z);
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();

	void virtual OnEvent(int eventType, Event * e);

	void virtual Update(float deltaTime);

private:

	Ogre::Vector3 _pos;
	Ogre::Vector3 _rot;
	Ogre::Vector3 _scale;

	bool _mustMove;

	float _auxPosX;
	float _auxPosY;
	float _auxPosZ;


};

#endif