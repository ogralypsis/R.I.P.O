#ifndef _H_TRANSFORMCOMPONENT_H_
#define _H_TRANSFORMCOMPONENT_H_

#include <Component.h>
#include "RIPOEvent.h"
#include "../Ogre/Transform.h"
#include "RIPOArguments.h"

struct position
{
	float _x;
	float _y;
	float _z;
};

struct rotation
{
	float _x;
	float _y;
	float _z;
};

struct scale
{
	float _x;
	float _y;
	float _z;
};

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	//Position
	void SetPosition(float x, float y, float z);
	position GetPosition();

	//Rotation
	void SetRotation(float x, float y, float z);
	rotation GetRotation();

	//Scale
	void SetScale(float x, float y, float z);
	scale GetScale();

	void virtual OnEvent(int eventType, Event e);

	void virtual Update();




private:

	position _pos;
	rotation _rot;
	scale _scale;

	Transform* t = nullptr;
};

#endif