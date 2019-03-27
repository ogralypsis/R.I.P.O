#include "RenderComponent.h"
#include "../Ogre/MyOgre.h"

#include <iostream>

RenderComponent::RenderComponent()
{
	MyOgre::GetInstance().CreateEntity("Sinbad.mesh");
	std::cout << "LLEGO HASTA AQUI CHATO\n";
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::OnEvent(Event e)
{
}

void RenderComponent::Update()
{
}
