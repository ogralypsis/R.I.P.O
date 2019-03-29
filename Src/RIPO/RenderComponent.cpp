#include "RenderComponent.h"
#include "../Ogre/MyOgre.h"

#include <iostream>

RenderComponent::RenderComponent() {}

RenderComponent::RenderComponent(/*Ogre::SceneManager * sceneMgr,*/ std::string mesh) 
{
	MyOgre::GetInstance().CreateEntity(/*sceneMgr,*/ mesh);
}

RenderComponent::~RenderComponent() {}

void RenderComponent::OnEvent(Event e)
{
	// Hay que comprobar que el emisor del evento es el mismo que el que lo recibe?¿?¡
	//if(_ownerEntity->GetId() == e.emitter.GetId())
	// Physics transform has been updated so update render properties in order to syncrhonize render and collider
	if ("UpdateTransformEvent" == typeid(e).name())
	{

	}
}

void RenderComponent::Update()
{
}
