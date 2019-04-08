#include "RenderComponent.h"
#include <MyOgre.h>
#include "RIPOEvent.h"
#include <iostream>

RenderComponent::RenderComponent() : Component () {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::map<std::string, Arguments> arguments, Entity * e) 
{
	_ownerEntity = e;
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

void RenderComponent::OnEvent(int eventType, Event e)
{
	// ---------------------------- TESTING -------------------------------
	if (_ownerEntity->GetId() == e.GetEmmitter()) {

		// Physics transform has been updated so update render properties in order to syncrhonize render and collider
		if (EventType::EVENT_UPDATE_TRANSFORM == eventType)
		{
			std::cout << "EVENTO UPDATE TRANSFORM RECIBIDO" << std::endl;
		}
	}
}

void RenderComponent::Update()
{
}
