#include "CEGUIUser.h"

CEGUIUser::CEGUIUser() : _myRenderer(CEGUI::OgreRenderer::bootstrapSystem())
{

}


CEGUIUser::~CEGUIUser()
{
	CEGUI::System::destroy();

	CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>(_myRenderer));
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