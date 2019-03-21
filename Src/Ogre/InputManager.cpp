#include "InputManager.h"



InputManager::InputManager() : _keyboardKeys(256, false), _mouseButtons(3, false) //or 3, test pending
{
	InitInput();
}

//Initialisation
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
	_inputSystem = OIS::InputManager::createInputSystem(_pl);

	//creates mouse object for the buffered input
	_mouse = static_cast<OIS::Mouse*>(_inputSystem->createInputObject(OIS::OISMouse, true));
	_mouse->setEventCallback(this);

	//creates keayboard objects for the buffered input
	_keyboard = static_cast<OIS::Keyboard*>(_inputSystem->createInputObject(OIS::OISKeyboard, true));
	_keyboard->setEventCallback(this);
	
	
	ResizeWindow(_renderWindow);

}

InputManager* InputManager::GetInstance()
{
	if (_instance)
		_instance = new InputManager();
	return _instance;
}

void InputManager::ResizeWindow(Ogre::RenderWindow* rw)
{
	_renderWindow = rw;
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
	if (_inputSystem) {
		if (_mouse) {
			_inputSystem->destroyInputObject(_mouse);
			_mouse = 0;
		}

		if (_keyboard) {
			_inputSystem->destroyInputObject(_keyboard);
			_keyboard = 0;
		}
		_inputSystem->destroyInputSystem(_inputSystem);
		_inputSystem = 0;

	}
}

//
void InputManager::CaptureInput()
{
	if (_mouse)
		_mouse->capture();
	if (_keyboard)
		_keyboard->capture();
}

///KEYBOARD

bool InputManager::keyPressed(const OIS::KeyEvent &e)
{
	_keyboardKeys[e.key] = true;
	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent &e)
{
	_keyboardKeys[e.key] = false;
	return true;
}

bool InputManager::GetKey(OIS::KeyCode key)
{
	return _keyboardKeys[key];
}

///MOUSE

bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	_mouseButtons[id] = true;
	return true;
}

bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	_mouseButtons[id] = false;
	return true;
}

bool InputManager::GetMouseButton(OIS::MouseButtonID id)
{
	return _mouseButtons[id];
}

bool InputManager::mouseMoved(const OIS::MouseEvent &e)
{
	_mouseX = e.state.X;
	_mouseY = e.state.Y;
	_mouseZ = e.state.Z;
	return true;
}


