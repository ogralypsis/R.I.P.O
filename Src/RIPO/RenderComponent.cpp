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

	_positionX = arguments["positionX"]._i;
	_positionY = arguments["positionY"]._i;
	_positionZ = arguments["positionZ"]._i;

	int _scaleX = arguments["scaleX"]._i;
	int _scaleY = arguments["scaleY"]._i;
	int _scaleZ = arguments["scaleZ"]._i;

	float _rotationX = arguments["rotationX"]._f;
	float _rotationY = arguments["rotationY"]._f;
	float _rotationZ = arguments["rotationZ"]._f;

	_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionY, _positionZ),Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotationX), Ogre::Radian(_rotationY), Ogre::Radian(_rotationZ));
	
	// TODO: COGER LOS VERTICES DEL BOUNDING BOX DE OGRE, PASARSELOS AL RIGIDBODY Y CREAR UNA CUSTOM SHAPE CON ELLOS
	//_entityOgre->getBoundingBox().getAllCorners();

}

void RenderComponent::OnEvent(int eventType, Event * e)
{	
		
		if (eventType == EventType::EVENT_UPDATE_TRANSFORM)
		{
			//std::cout << "EVENTO UPDATE TRANSFORM RECIBIDO" << std::endl;
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

		//std::cout << "POS Y RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().z << std::endl;
		//std::cout << "POS Z RENDER : " + _ownerEntity->GetId() + " " << _entityOgre->getParentSceneNode()->getPosition().y << std::endl;
		

	}

	
}

void RenderComponent::GetEntitySize()
{
	//_entityOgre->getParentSceneNode()->

}

std::vector<int> RenderComponent::GetPosition()
{
	std::vector<int> position = { _positionX, _positionY, _positionZ };
	return position;
}

/*Ogre::SceneNode * RenderComponent::GetNode()
{
	return _entityNode;
}*/
	
