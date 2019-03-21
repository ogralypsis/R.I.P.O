#ifndef _H_INPUTMANAGER_H_
#define _H_INPUTMANAGER_H_

#include "MyOgre.h"
#include "OIS.h"
#include <vector>

///<sumary>
//how to get input from another class
//InputManager::GetInstance()->GetKey(OIS::KeyCode::KC_A);
//InputManager::GetInstance()->GetMouseButton(OIS::MouseButtonID::MB_Right);
///<sumary>

class InputManager : public OIS::KeyListener, public OIS::MouseListener
{
public:
	InputManager();
	~InputManager();

	void CaptureInput();

	static InputManager* GetInstance();
	
	void ResizeWindow(Ogre::RenderWindow* rw);
private:

	///InputSystem
	static InputManager* _instance;

	OIS::InputManager* _inputSystem = nullptr;

	Ogre::RenderWindow* _renderWindow = nullptr;
	OIS::ParamList _pl; 
	size_t windowHnd;
	std::ostringstream windowHndStr;

	void InitInput(); //InputManager initialisation
	
	///KEYBOARD
	OIS::Keyboard* _keyboard = nullptr;

	std::vector<bool> _keyboardKeys;
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
	bool GetKey(OIS::KeyCode);
	
	///MOUSE
	OIS::Mouse* _mouse = nullptr;

	std::vector<bool> _mouseButtons;
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool GetMouseButton(OIS::MouseButtonID);
	//mouse cursor coordinates
	OIS::Axis _mouseX, _mouseY, _mouseZ;
};

#endif