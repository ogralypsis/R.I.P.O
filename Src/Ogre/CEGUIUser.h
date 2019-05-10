#ifndef _H_CEGUIUSER_H_
#define _H_CEGUIUSER_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <glm/glm.hpp>
#include <OISMouse.h>

class CEGUIUser
{
public:
	~CEGUIUser();
	static CEGUIUser* GetInstance();
	void ResetInstance();

	bool Init(const std::string dir);
	void SetUpScene();
	void Destroy();
	void Release();

	void Draw();

	void LoadScheme(const std::string& schemeFile);
	void SetFont(const std::string& fontFile);
	void SetCursor(const std::string& mouseFile);

	void OnMouseReleased(OIS::MouseButtonID id);
	CEGUI::MouseButton ConvertButton(OIS::MouseButtonID buttonID);
	void UpdateMouseCoords(float x, float y);
	void UpdateTime(float t);

	CEGUI::Window* CreateWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, 
		const std::string & text, const std::string& name = "");
	static void SetWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

	// Getters
	static CEGUI::OgreRenderer* GetRenderer();
	CEGUI::GUIContext* GetContext();

private:
	CEGUIUser();

	// Instance for singleton
	static CEGUIUser* _instance;

	static CEGUI::OgreRenderer* _renderer;
	CEGUI::GUIContext* _context;
	CEGUI::Window* _window;
};
#endif
