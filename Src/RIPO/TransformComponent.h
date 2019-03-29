#ifndef _H_TRANSFORMCOMPONENT_H_
#define _H_TRANSFORMCOMPONENT_H_

#include <../Engine/Component.h>
#include "RIPOEvent.h"
#include "../Ogre/Transform.h"

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
	TransformComponent(std::string arg);
	TransformComponent(std::string id, Entity* e);
	~TransformComponent();

	//Position
	void SetPosition(float x, float y, float z);
	position GetPosition() { return _pos; };

	//Rotation
	void SetRotation(float x, float y, float z);
	rotation GetRotation() { return _rot; };

	//Scale
	void SetScale(float x, float y, float z);
	scale GetScale() { return _scale; };

	void virtual OnEvent(Event e);

	void virtual Update();




private:

	position _pos;
	rotation _rot;
	scale _scale;

	Transform* t = nullptr;
};

#endif