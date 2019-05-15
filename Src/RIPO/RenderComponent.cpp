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
	_mustRotate = false;

	std::string _mesh = arguments["mesh"]._str;

	_positionX = arguments["positionX"]._f;
	_positionY = arguments["positionY"]._f;
	_positionZ = arguments["positionZ"]._f;

	float _scaleX = arguments["scaleX"]._f;
	float _scaleY = arguments["scaleY"]._f;
	float _scaleZ = arguments["scaleZ"]._f;

	float _rotationX = arguments["rotationX"]._f;
	float _rotationY = arguments["rotationY"]._f;
	float _rotationZ = arguments["rotationZ"]._f;

	_entityOgre = MyOgre::GetInstance().CreateEntity(_mesh, Ogre::Vector3(_positionX, _positionZ, _positionY),Ogre::Vector3(_scaleX, _scaleY, _scaleZ), Ogre::Radian(_rotationX), Ogre::Radian(_rotationY), Ogre::Radian(_rotationZ));
	

	 _auxPosX = 0.0f;
	 _auxPosY = 0.0f;
	 _auxPosZ = 0.0f;
	// TODO: COGER LOS VERTICES DEL BOUNDING BOX DE OGRE, PASARSELOS AL RIGIDBODY Y CREAR UNA CUSTOM SHAPE CON ELLOS
	//_entityOgre->getBoundingBox().getAllCorners();

}

void RenderComponent::OnEvent(int eventType, Event * e)
{	
		
		if (eventType == EventType::EVENT_UPDATE_TRANSFORM && e->GetEmmitter() == _ownerEntity->GetId())
		{
		
			_mustMove = true;
			_auxPosX = static_cast<UpdateTransformEvent*>(e)->_posX;
			_auxPosY = static_cast<UpdateTransformEvent*>(e)->_posY;
			_auxPosZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
		}
}

void RenderComponent::Update(float deltaTime)
{	

	if (_mustMove) {
		_entityOgre->getParentSceneNode()->setPosition(Ogre::Vector3(_auxPosX, _auxPosY, _auxPosZ));	
	
		_mustMove = false;	
	}	
}

void RenderComponent::GetEntitySize()
{
	//_entityOgre->getParentSceneNode()->

}

Pos RenderComponent::GetPosition()
{
	Pos position(_positionX, _positionY, _positionZ);
	return position;
}

Quat RenderComponent::GetOrientation()
{

	Ogre::Matrix3 m = Ogre::Matrix3();
	Ogre::Quaternion qAux = _entityOgre->getParentSceneNode()->getOrientation();
	Quat q(qAux.w, qAux.x, qAux.y, qAux.z);

	return q;
}

Ogre::SceneNode * RenderComponent::GetNode()
{
	return _entityOgre->getParentSceneNode();
}
	
