#include "CEGUIUser.h"

CEGUIUser * CEGUIUser::_instance = nullptr;

CEGUIUser::CEGUIUser() : _myRenderer(CEGUI::OgreRenderer::bootstrapSystem())
{

}


CEGUIUser::~CEGUIUser()
{
	CEGUI::System::destroy();
	CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>(_myRenderer));
}

void CEGUIUser::CreateButton(std::string name, CEGUI::UVector2 pos, CEGUI::USize size)
{
	CEGUI::Window *gJumpBtnWindow = NULL;

	// creates button of type TaharezLook/Button, with name "name"
	gJumpBtnWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", name);  // Create Window
	// set the position and the size
	gJumpBtnWindow->setPosition(pos);
	gJumpBtnWindow->setSize(size);
	// set the text of the button, the same as the name of the button
	gJumpBtnWindow->setText(name);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(gJumpBtnWindow);

	delete gJumpBtnWindow;
}


void CEGUIUser::Render()
{
	_myRenderer.beginRendering();

	CEGUI::System::getSingleton().renderAllGUIContexts();
}

CEGUIUser * CEGUIUser::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CEGUIUser();

	return _instance;
}