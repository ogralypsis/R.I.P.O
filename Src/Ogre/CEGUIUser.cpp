#include "CEGUIUser.h"
#include "MyOgre.h"

CEGUIUser * CEGUIUser::_instance = nullptr;
CEGUI::OgreRenderer* CEGUIUser::_renderer = nullptr;

CEGUIUser::CEGUIUser() 
{
	_context = nullptr;
	_window = nullptr;
}

CEGUIUser::~CEGUIUser() {}

bool CEGUIUser::Init(const std::string dir)
{
	try {
		// check if renderer and system were already initialized
		if (_renderer == nullptr) {
			_renderer = &CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(MyOgre::GetInstance().GetWindow()));

			// set up resource directories
			CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
			rp->setResourceGroupDirectory("imagesets", dir + "/imagesets/");
			rp->setResourceGroupDirectory("schemes", dir + "/schemes/");
			rp->setResourceGroupDirectory("fonts", dir + "/fonts/");
			rp->setResourceGroupDirectory("layouts", dir + "/layouts/");
			rp->setResourceGroupDirectory("looknfeels", dir + "/looknfeel/");
			rp->setResourceGroupDirectory("lua_scripts", dir + "/lua_scripts/");

			// tell them where they find their resources
			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		}

		// the context renders using our renderer
		_context = &CEGUI::System::getSingleton().createGUIContext(_renderer->getDefaultRenderTarget());
		// create the window
		_window = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "window");
		// set the window for that context
		_context->setRootWindow(_window);

		return true;
	}
	catch (CEGUI::Exception& e) {
		e.getMessage();
		return false;
	}
}

void CEGUIUser::Destroy()
{
	// destroy our context
	CEGUI::System::getSingleton().destroyGUIContext(*_context);
}

// render our GUI
void CEGUIUser::Draw()
{
	_renderer->beginRendering();
	_context->draw();
	_renderer->endRendering();

	//glDisable(GL_SCISSOR_TEST); // so it doesn't flicker
}

void CEGUIUser::LoadScheme(const std::string & schemeFile)
{
	// scheme has the "how the widget will look"
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void CEGUIUser::SetFont(const std::string & fontFile)
{
	// load font
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	// set font for all widgets of _context
	_context->setDefaultFont(fontFile);
}

void CEGUIUser::SetMouseCursor(const std::string & mouseFile)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(mouseFile + ".scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(mouseFile + "/MouseArrow");
}

CEGUI::Window * CEGUIUser::CreateWidget(const std::string & type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string & name)
{
	// type -> type of widget (i.e., "Push Button")

	// create the widget but doesn't render it
	CEGUI::Window* newWidget = CEGUI::WindowManager::getSingleton().createWindow(type, name); 
	// now it will get rendered
	_window->addChild(newWidget);

	// set position and size of widget
	SetWidgetDestRect(newWidget, destRectPerc, destRectPix);

	return newWidget;
}

void CEGUIUser::SetWidgetDestRect(CEGUI::Window * widget, const glm::vec4 & destRectPerc, const glm::vec4 & destRectPix)
{
	// set position and size of widget
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

CEGUI::OgreRenderer* CEGUIUser::GetRenderer() { return _renderer; }

CEGUI::GUIContext * CEGUIUser::GetContext() { return _context; }

CEGUIUser * CEGUIUser::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CEGUIUser();

	return _instance;
}