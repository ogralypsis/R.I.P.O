#include "InputManager.h"

//static variable for singleton
InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() : _mouse(0), _keyboard(0), _inputSystem(0), _keyboardKeys(256, false), _mouseButtons(3, false) //or 3, test pending
{
	//InitInput();

}
//Initialisation
bool InputManager::InitInput(Ogre::RenderWindow* rw)
{
	windowHnd = 0;

	//Get window handle
	_renderWindow = rw;
	_renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd; //string representation of window handle
	_pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	/*//Allows the user to use the mouse outside of the application if application is not in fullscreen mode
#if defined OIS_WIN32_PLATFORM
	_pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	_pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	_pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	_pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#endif*/

	//creates input manager
	_inputSystem = OIS::InputManager::createInputSystem(_pl);


	//creates mouse object for the buffered input
	_mouse = static_cast<OIS::Mouse*>(_inputSystem->createInputObject(OIS::OISMouse, true));
	_mouse->setEventCallback(this);

	//creates keayboard objects for the buffered input
	_keyboard = static_cast<OIS::Keyboard*>(_inputSystem->createInputObject(OIS::OISKeyboard, true));
	_keyboard->setEventCallback(this);


	ResizeWindow(_renderWindow);

	if(!_inputSystem || !_mouse || !_keyboard)
		return false;
	else return true;
}

InputManager& InputManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new InputManager();
	return *InputManager::_instance;
}

void InputManager::ResetInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
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

	//check if this works 
	_mouseState.width = width;
	_mouseState.height = height;
}

InputManager::~InputManager()
{
	if (_inputSystem) {
		if (_mouse != nullptr) {
			_inputSystem->destroyInputObject(_mouse);
			_mouse = nullptr;
		}

		if (_keyboard) {
			_inputSystem->destroyInputObject(_keyboard);
			_keyboard = nullptr;
		}

		_inputSystem->destroyInputSystem(_inputSystem);
	}
}

//
void InputManager::CaptureInput()
{
	_mouseMove = false;
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

bool InputManager::IsKeyDown(OIS::KeyCode key)
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

bool InputManager::IsMouseButtonPressed(OIS::MouseButtonID id)
{
	return _mouseButtons[id];
}

bool InputManager::mouseMoved(const OIS::MouseEvent &e)
{
	_mousePosition.mouseX = e.state.X.rel;
	_mousePosition.mouseY = e.state.Y.rel;
	_mousePosition.mouseZ = e.state.Z.rel;

	_mouseMove = true;

	return true;
}

mouseCoordinates InputManager::GetMouseCoords()
{
	return _mousePosition;
}

bool InputManager::GetMouseMove()
{
	return _mouseMove;
}



