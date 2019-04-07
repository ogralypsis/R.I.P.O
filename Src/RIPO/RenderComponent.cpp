#include "RenderComponent.h"
#include <MyOgre.h>
#include "RIPOEvent.h"
#include <iostream>

RenderComponent::RenderComponent() : Component () {}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	std::string mesh = arguments["mesh"].str;
	MyOgre::GetInstance().CreateEntity(mesh);

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
