#include "InputManager.h"



InputManager::InputManager() : _keyboardKeys(256, false), _mouseKeys(8, false) //or 3, test pending
{
	InitInput();
}


void InputManager::InitInput()
{
	windowHnd = 0;
	
	//Get window handle
	_renderWindow = MyOgre::GetInstance().GetWindow();
	_renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd; //string representation of window handle
	_pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Allows the user to use the mouse outside of the application if application is not in fullscreen mode
#if defined OIS_WIN32_PLATFORM
	_pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	_pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	_pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	_pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#endif

	//creates input manager
	_inputManager = OIS::InputManager::createInputSystem(_pl);

	//creates keayboard and mouse objects for the buffered input
	_mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(OIS::OISMouse, true));
	_mouse->setEventCallback(this);

	_keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(OIS::OISKeyboard, true));
	_keyboard->setEventCallback(this);
	
	//Pass window metrics to OIS
	unsigned int width, height, depth;
	int top, left;
	_renderWindow->getMetrics(width, height, depth, left, top);

	//creates mouse state
	const OIS::MouseState & _mouseState = _mouse->getMouseState();

	_mouseState.width = width;
	_mouseState.height = height;


	
}


InputManager::~InputManager()
{
	if (_inputManager) {
		if (_mouse) {
			_inputManager->destroyInputObject(_mouse);
			_mouse = 0;
		}

		if (_keyboard) {
			_inputManager->destroyInputObject(_keyboard);
			_keyboard = 0;
		}
		_inputManager->destroyInputSystem(_inputManager);
	}
}

bool InputManager::KeyPressed(const OIS::KeyEvent &e)
{
	_keyboardKeys[e.key] = true;
	return true;
}


bool InputManager::MousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	_mouseKeys[id] = true;
	return true;
}

bool InputManager::MouseMoved(const OIS::MouseEvent &e)
{
	_mouseX = e.state.X;
	_mouseY = e.state.Y;
	_mouseZ = e.state.Z;
	return true;
}

void InputManager::CaptureInput()
{
	if (_mouse)
		_mouse->capture();
	if (_keyboard)
		_keyboard->capture();
}