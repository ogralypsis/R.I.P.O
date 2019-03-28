#include "RenderComponent.h"
#include "../Ogre/MyOgre.h"

#include <iostream>

RenderComponent::RenderComponent() {}

RenderComponent::RenderComponent(std::string mesh)
{
	MyOgre::GetInstance().CreateEntity(mesh);
}

RenderComponent::~RenderComponent() {}

void RenderComponent::OnEvent(Event e)
{
}

void RenderComponent::Update()
{
}
