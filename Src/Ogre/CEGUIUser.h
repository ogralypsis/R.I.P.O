#ifndef _H_CEGUIUSER_H_
#define _H_CEGUIUSER_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class CEGUIUser
{
public:
	void Render();

	static CEGUIUser* GetInstance();

	~CEGUIUser();

private:
	CEGUIUser();

	// Instance for singleton
	static CEGUIUser* _instance;

	CEGUI::OgreRenderer& _myRenderer;
};
#endif
