#ifndef _H_CEGUIUSER_H_
#define _H_CEGUIUSER_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>

class CEGUIUser
{
public:
	~CEGUIUser();
	static CEGUIUser* GetInstance();


	bool Init(const std::string dir);
	void Destroy();

	void Draw();

	void LoadScheme(const std::string& schemeFile);
	void SetFont(const std::string& fontFile);
	// Getters
	static CEGUI::OpenGL3Renderer* GetRenderer();
	CEGUI::GUIContext* GetContext();

	void Render();

	void CreateButton(std::string name, CEGUI::UVector2 pos, CEGUI::USize size);



private:
	CEGUIUser();

	// Instance for singleton
	static CEGUIUser* _instance;

	static CEGUI::OpenGL3Renderer* _renderer;

	CEGUI::GUIContext* _context;
};
#endif
