#ifndef _H_INPUTMANAGER_H_
#define _H_INPUTMANAGER_H_

#include "MyOgre.h"
#include <OIS.h>
#include <vector>

class InputManager : public OIS::KeyListener, public OIS::MouseListener
{
public:
	InputManager();
	~InputManager();

	void CaptureInput();

	
private:
	void InitInput();

	OIS::InputManager* _inputManager = nullptr;
	OIS::Mouse* _mouse = nullptr;
	OIS::Keyboard* _keyboard = nullptr;

	Ogre::RenderWindow* _renderWindow = nullptr;

	OIS::ParamList _pl; 
	size_t windowHnd;
	std::ostringstream windowHndStr;

	//buffers
	std::vector<bool> _keyboardKeys;
	std::vector<bool> _mouseKeys;


	bool KeyPressed(const OIS::KeyEvent &e);


	bool MousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool MouseMoved(const OIS::MouseEvent &e);

	//mouse cursor coordinates
	OIS::Axis _mouseX, _mouseY, _mouseZ;
};

#endif