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

			// tell them where they find their resources
			CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
			CEGUI::Scheme::setDefaultResourceGroup("Schemes");
			CEGUI::Font::setDefaultResourceGroup("Fonts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeels");
			CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("Lua_Scripts");
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
	_context = nullptr;
}

void CEGUIUser::Release()
{
	// destroy context
	Destroy();
	// destroy renderer
	_renderer = nullptr;
	// destroy window
	_window = nullptr;
}

// render our GUI
void CEGUIUser::Draw()
{
	if (_context != nullptr) {
		_renderer->beginRendering();
		_context->draw();
		_renderer->endRendering();
	}
}

void CEGUIUser::LoadScheme(const std::string & schemeFile)
{
	try {
		// scheme has the "how the widget will look"
		CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile + ".scheme");
	}
	catch (Ogre::Exception& e) {
		e.getFullDescription();
	}
}

void CEGUIUser::SetFont(const std::string & fontFile)
{
	try {
		// load font
		CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
		// set font for all widgets of _context
		_context->setDefaultFont(fontFile);
	}
	catch (Ogre::Exception& e) {
		e.getFullDescription();
	}
}

void CEGUIUser::SetCursor(const std::string & mouseFile)
{
	try {
		// set font for all widgets of _context
		_context->getMouseCursor().setDefaultImage(mouseFile + "/MouseArrow");
	}
	catch (Ogre::Exception& e) {
		e.getFullDescription();
	}
}

void CEGUIUser::OnMouseReleased(OIS::MouseButtonID id)
{
	// the button has been clicked
	if (_context != nullptr)
		if (_context->injectMouseButtonDown(ConvertButton(id)) && _context->injectMouseButtonUp(ConvertButton(id)))
			printf("%s \n", "OVER WINDOW");
}

CEGUI::MouseButton CEGUIUser::ConvertButton(OIS::MouseButtonID buttonID)
{
	// convert from OIS type to CEGUI type
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	}
}

void CEGUIUser::UpdateMouseCoords(float x, float y)
{
	if (_context != nullptr) {
		_context->injectMouseMove(x, y);
	}
}

void CEGUIUser::UpdateTime(float t)
{
	if (_context != nullptr) {
		//Need to inject timestamps to CEGUI System.
		_context->injectTimePulse(t);
	}
}

CEGUI::Window * CEGUIUser::CreateWidget(const std::string & type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string & text, const std::string & name)
{
	// type -> type of widget (i.e., "Push Button")

	CEGUI::Window* newWidget = nullptr;

	try {
		// create the widget but doesn't render it
		newWidget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
		
		// now it will get rendered
		_window->addChild(newWidget);
		
		// set position and size of widget
		SetWidgetDestRect(newWidget, destRectPerc, destRectPix);

		// add text
		newWidget->setText(text);
	}
	catch (CEGUI::Exception& e) {
		e.getMessage();
	}
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

void CEGUIUser::ResetInstance()
{
	if (CEGUIUser::_instance != nullptr) {
		delete CEGUIUser::_instance;
		CEGUIUser::_instance = nullptr;
	}
}
