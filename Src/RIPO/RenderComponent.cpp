#include "RenderComponent.h"
#include <MyOgre.h>

RenderComponent::RenderComponent() : Component () {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	std::string _mesh = arguments["mesh"].str;

	int _positionX = arguments["positionX"].i;
	int _positionY = arguments["positionY"].i;
	int _positionZ = arguments["positionZ"].i;

	int _scaleX = arguments["scaleX"].i;
	int _scaleY = arguments["scaleY"].i;
	int _scaleZ = arguments["scaleZ"].i;

	int _rotation = arguments["rotation"].i;

	MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionY, _positionZ), 
		Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotation));
}

void RenderComponent::OnEvent(Event e)
{
	// Hay que comprobar que el emisor del evento es el mismo que el que lo recibe?�?�
	//if(_ownerEntity->GetId() == e.emitter.GetId())
	// Physics transform has been updated so update render properties in order to syncrhonize render and collider
	if ("UpdateTransformEvent" == typeid(e).name())
	{

	}
}

void RenderComponent::Update()
{
}
