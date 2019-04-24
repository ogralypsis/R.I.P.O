#ifndef _H_CEGUIUSER_H_
#define _H_CEGUIUSER_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class CEGUIUser
{
public:
	~CEGUIUser();
	static CEGUIUser* GetInstance();

	void Render();

	void CreateButton(std::string name, CEGUI::UVector2 pos, CEGUI::USize size);



private:
	CEGUIUser();

	// Instance for singleton
	static CEGUIUser* _instance;

	CEGUI::OgreRenderer& _myRenderer;
};
#endif
