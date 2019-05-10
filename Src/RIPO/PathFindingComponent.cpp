#include "PathFindingComponent.h"

PathFindingComponent::PathFindingComponent() : Component() {}

PathFindingComponent::~PathFindingComponent() {}

void PathFindingComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

}

void PathFindingComponent::OnEvent(int eventType, Event * e) {}

void PathFindingComponent::Update(float deltaTime) {
	
	/*
	CODIGO DE OTRO PROYECTO HECHO CON OGRE
			Ogre::Vector3 angIni(0, 0, 1);
			Ogre::Vector3 angFin(entidadHeroe->getPox() - entidad->getPox(), 0, entidadHeroe->getPoz() - entidad->getPoz());
			node->setOrientation(angIni.getRotationTo(angFin));
			node->translate(node->getOrientation() * Ogre::Vector3(0, 0, 0.1));
			entidad->GetComponent(rb)->actualizarPos(node->getPosition().x, node->getPosition().y, node->getPosition().z);
	HAY FORMAS MEJORES DE HACERLO? SEGURAMENTE
	*/
}
