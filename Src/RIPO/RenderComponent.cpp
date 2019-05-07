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

	_mustMove = false;

	std::string _mesh = arguments["mesh"].str;

	int _positionX = arguments["positionX"].i;
	int _positionY = arguments["positionY"].i;
	int _positionZ = arguments["positionZ"].i;

	int _scaleX = arguments["scaleX"].i;
	int _scaleY = arguments["scaleY"].i;
	int _scaleZ = arguments["scaleZ"].i;

	int _rotation = arguments["rotation"].i;

	if (_transform != nullptr) {
		_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_transform->GetPosX(),_transform->GetPosZ(), _transform->GetPosY()),
			Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotation));
	}
	else {
		_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionY, _positionZ),
			Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotation));
	}

}

void RenderComponent::OnEvent(int eventType, Event * e)
{	
		// Physics transform has been updated so update render properties in order to syncrhonize render and collider
	//if (_ownerEntity->GetId() == e->GetEmmitter()) {
		if (eventType == EventType::EVENT_UPDATE_TRANSFORM)
		{
			std::cout << "EVENTO UPDATE TRANSFORM RECIBIDO" << std::endl;
			_mustMove = true;
			_auxPosX = static_cast<UpdateTransformEvent*>(e)->_posX;
			_auxPosY = static_cast<UpdateTransformEvent*>(e)->_posY;
			_auxPosZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
		}
	//}
}

void RenderComponent::Update(float deltaTime)
{	
	if (_mustMove) {
		_entityOgre->getParentSceneNode()->setPosition(Ogre::Vector3(_auxPosX, _auxPosZ, _auxPosY));
		_mustMove = false;

		std::cout << "POS Y RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().z << std::endl;
		std::cout << "POS Z RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().y << std::endl;

	}
	
}
	
