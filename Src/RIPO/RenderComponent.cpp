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

	_mustMove = false;

	std::string _mesh = arguments["mesh"]._str;

	int _positionX = arguments["positionX"]._i;
	int _positionY = arguments["positionY"]._i;
	int _positionZ = arguments["positionZ"]._i;

	int _scaleX = arguments["scaleX"]._i;
	int _scaleY = arguments["scaleY"]._i;
	int _scaleZ = arguments["scaleZ"]._i;

	float _rotation = arguments["rotation"]._f;

	_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionY, _positionZ),Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotation), Ogre::Radian(0), Ogre::Radian(0));
	

}

void RenderComponent::OnEvent(int eventType, Event * e)
{	
		
		if (eventType == EventType::EVENT_UPDATE_TRANSFORM)
		{
			std::cout << "EVENTO UPDATE TRANSFORM RECIBIDO" << std::endl;
			_mustMove = true;
			_auxPosX = static_cast<UpdateTransformEvent*>(e)->_posX;
			_auxPosY = static_cast<UpdateTransformEvent*>(e)->_posY;
			_auxPosZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
		}

}

void RenderComponent::Update(float deltaTime)
{	
	/*if (_mustMove) {
		_entityNode->setPosition(Ogre::Vector3(_auxPosX, _auxPosZ, _auxPosY));
		_mustMove = false;

		std::cout << "POS Y RENDER : " + _ownerEntity->GetId() + " " << _entityNode->getParentSceneNode()->getPosition().z << std::endl;
		std::cout << "POS Z RENDER : " + _ownerEntity->GetId() + " " << _entityNode->getParentSceneNode()->getPosition().y << std::endl;

	}*/

	if (_mustMove) {
		_entityOgre->getParentSceneNode()->setPosition(Ogre::Vector3(_auxPosX, _auxPosZ, _auxPosY));
		_mustMove = false;

		std::cout << "POS Y RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().z << std::endl;
		std::cout << "POS Z RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().y << std::endl;

	}

	
}

/*Ogre::SceneNode * RenderComponent::GetNode()
{
	return _entityNode;
}*/
	
