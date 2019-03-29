#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <Component.h>
#include <OgreSceneManager.h>

class RenderComponent :
	public Component
{
public:
	RenderComponent();
	RenderComponent(/*Ogre::SceneManager * sceneMgr, */std::string mesh);
	~RenderComponent();

	void virtual OnEvent(Event e);
	void virtual Update();

};

#endif RENDER_COMPONENT_H
