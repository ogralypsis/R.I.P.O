#include "CEGUIUser.h"

CEGUIUser * CEGUIUser::_instance = nullptr;
CEGUI::OpenGL3Renderer* CEGUIUser::_renderer = nullptr;

CEGUIUser::CEGUIUser() 
{
	_context = nullptr;
}

CEGUIUser::~CEGUIUser() {}


bool CEGUIUser::Init(const std::string dir)
{
	try {
		// check if renderer and system were already initialized
		if (_renderer == nullptr) {
			_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

			// set up resource directories
			CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
			rp->setResourceGroupDirectory("imagesets", dir + "/imagesets/");
			rp->setResourceGroupDirectory("schemes", dir + "/schemes/");
			rp->setResourceGroupDirectory("fonts", dir + "/fonts/");
			rp->setResourceGroupDirectory("layouts", dir + "/layouts/");
			rp->setResourceGroupDirectory("looknfeels", dir + "/looknfeels/");
			rp->setResourceGroupDirectory("lua_scripts", dir + "/lua_scripts/");

			// tell them where they find their resources
			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		}

		_context = &CEGUI::System::getSingleton().createGUIContext(_renderer->getDefaultRenderTarget());

		return true;
	}
	catch (CEGUI::Exception& e) {
		return false;
	}
}

void CEGUIUser::Destroy()
{
}

void CEGUIUser::Draw()
{
}

void CEGUIUser::LoadScheme(const std::string & schemeFile)
{
	// scheme has the "how the widget will look"
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void CEGUIUser::SetFont(const std::string & fontFile)
{
	// set font for all widgets of _context
	_context->setDefaultFont(fontFile);
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



CEGUI::OpenGL3Renderer* CEGUIUser::GetRenderer()
{
	return _renderer;
}

CEGUI::GUIContext * CEGUIUser::GetContext()
{
	return _context;
}

void CEGUIUser::Render()
{

}

CEGUIUser * CEGUIUser::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CEGUIUser();

	return _instance;
}