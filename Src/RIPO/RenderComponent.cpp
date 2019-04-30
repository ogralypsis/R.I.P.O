#include "RenderComponent.h"

// singleton
#include <MyOgre.h>

// events from RIPO
#include "RIPOEvent.h"

// other tools
#include <iostream>

RenderComponent::RenderComponent() : Component () {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::map<std::string, Arguments> arguments, Entity * e) 
{
	_ownerEntity = e;
	_id = "Render";

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform"));

	std::string _mesh = arguments["mesh"].str;

	int _positionX = arguments["positionX"].i;
	int _positionY = arguments["positionY"].i;
	int _positionZ = arguments["positionZ"].i;

	int _scaleX = arguments["scaleX"].i;
	int _scaleY = arguments["scaleY"].i;
	int _scaleZ = arguments["scaleZ"].i;

	int _rotation = arguments["rotation"].i;

	_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionY, _positionZ), 
		Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotation));
}

void RenderComponent::OnEvent(int eventType, Event e)
{

	// Doing without events, both Render and Rigidbody components have a transform object to update positions
	/*// ---------------------------- TESTING -------------------------------
	if (_ownerEntity->GetId() == e.GetEmmitter()) {

		// Physics transform has been updated so update render properties in order to syncrhonize render and collider
		if (EventType::EVENT_UPDATE_TRANSFORM == eventType)
		{
			std::cout << "EVENTO UPDATE TRANSFORM RECIBIDO" << std::endl;
		}
	}*/
}

void RenderComponent::Update(float deltaTime)
{	
	if (_transform != nullptr) {
		_entityOgre->getParentSceneNode()->translate(Ogre::Vector3(_transform->GetPosX(), _transform->GetPosY(), _transform->GetPosZ()));
		std::cout << "POS Z RENDER : " << _entityOgre->getParentSceneNode()->getPosition().z << std::endl;
	}
	
}
	
