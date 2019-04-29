#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <Component.h>
#include "TransformComponent.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event e);
	void virtual Update(float deltaTime);

private:

	TransformComponent * _transform = nullptr;
	Ogre::Entity * _entityOgre;
};

#endif RENDER_COMPONENT_H
