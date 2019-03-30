#include "RenderComponent.h"
#include <MyOgre.h>

RenderComponent::RenderComponent() : Component () {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	std::string mesh = arguments["mesh"].str;
	MyOgre::GetInstance().CreateEntity(mesh);

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
