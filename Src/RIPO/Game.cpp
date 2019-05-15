#include "Game.h"

// physx
#include <MyPhysX.h>
// ogre
#include <MyOgre.h>
#include <InputManager.h>
#include <CEGUIUser.h>
// engine
#include <EventManager.h>

// Event
#include "RIPOEvent.h"
// Components
#include "HealthComponent.h"
#include "RenderComponent.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "ButtonComponent.h"
#include "ExitButtonComponent.h"
#include "PathFindingComponent.h"
#include "BulletComponent.h"

// other tools
#include <Windows.h>
#include <time.h>
#include <iostream>


// Static variable for the singleton
Game * Game::_instance = nullptr;

Game::Game()
{	
	_exit = false;

	_currentTime = 0;
	_deltaTime = 0; 
	_timeSinceLastFrame = 0;
	_timer = new Ogre::Timer();

}


Game::~Game()
{
	_timer = nullptr;
	delete _timer;
}

bool Game::Init()
{
	// If OGRE's initialization fail return false
	if (!MyOgre::GetInstance().Init()) {
#ifdef _DEBUG
		std::cout << "OGRE couldn't be initialized" << std::endl;
#endif
		return false;
	}

	if (!MyPhysX::GetInstance().Init()) {
#ifdef _DEBUG
		std::cout << "PhysX couldn't be initialized" << std::endl;
#endif
		return false;
	}

	if (!InputManager::GetInstance().InitInput(MyOgre::GetInstance().GetWindow())) {
#ifdef _DEBUG		
		std::cout << "OIS Input system could not be initialized" << std::endl;
#endif	
	}

	
	// initialize GUI
	if (!CEGUIUser::GetInstance()->Init("Assets/CEGUI")) {
#ifdef _DEBUG		
		std::cout << "CEGUI system could not be initialized" << std::endl;
#endif	
	}
	else {
		CEGUIUser::GetInstance()->LoadScheme("AlfiskoSkin");
	}
	
	RegisterComponents();

	ChangeScene("0");


	return true;
}

void Game::Release()
{
	// Delete CeGUI
	CEGUIUser::GetInstance()->Release();

	// Release MyOgre
	MyOgre::GetInstance().Shutdown();
	// Delete MyOgre instance
	MyOgre::ResetInstance();

	// Release MyPhysX
	MyPhysX::GetInstance().Shutdown();
	// Delete MyPhysX instance
	MyPhysX::GetInstance().ResetInstance();
}

void Game::Loop()
{
	// Continue the loop if the window is not closed and game is not exited
	while (!MyOgre::GetInstance().CheckWindowStatus() && !_exit) 
	{
		_currentTime = _timer->getMilliseconds();
		_deltaTime = (_currentTime - _timeSinceLastFrame) / 100; // 1000 �?�?�?�?

		// do we need to change scene?
		if (_change)
			ChangeScene(_nextScene);

		MessagePump();

		// INPUT
		HandleInput();
			
		// PHYSCS STEP
		// ESCENA->UPDATE: physxScene->simulate
			
		// CURRENT SCENE UPDATE
		_states.top()->Update(_deltaTime);
			
		Render();


		_timeSinceLastFrame = _currentTime;
	}
}

Game & Game::GetInstance()
{
	// If there wasn't created an instance for Game create a new one
	if (Game::_instance == nullptr)
		Game::_instance = new Game();

	return *Game::_instance;
}

void Game::ResetInstance()
{
	if (Game::_instance != nullptr) {
		delete Game::_instance;
		Game::_instance = nullptr;
	}
}

void Game::HandleInput()
{
	//capture Input
	UpdateInput();
	
	//Once input is captures, check input
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_W))
	{
		//std::cout << "PRESSING KEY W" << std::endl;
		WEvent * wEvent = new WEvent(0, { 0, 0, 1 }, _states.top()->GetId(), EventDestination::SCENE);		
		EventManager::GetInstance()->NotifyObservers(wEvent->GetType(), wEvent);
	}
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_S))
	{
		//std::cout << "PRESSING KEY S" << std::endl;
		SEvent * sEvent = new SEvent(0, { 0, 0, -1 }, _states.top()->GetId(), EventDestination::SCENE);		
		EventManager::GetInstance()->NotifyObservers(sEvent->GetType(), sEvent);
	}
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_A))
	{
		//std::cout << "PRESSING KEY A" << std::endl;
		AEvent * aEvent = new AEvent(0, { 1, 0, 0 }, _states.top()->GetId(), EventDestination::SCENE);		
		EventManager::GetInstance()->NotifyObservers(aEvent->GetType(), aEvent);
	}
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_D))
	{
		//std::cout << "PRESSING KEY D" << std::endl;
		DEvent * dEvent = new DEvent(0, { -1, 0, 0 }, _states.top()->GetId(), EventDestination::SCENE);		
		EventManager::GetInstance()->NotifyObservers(dEvent->GetType(), dEvent);
	}
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_J))
	{
		JEvent * jEvent = new JEvent(_states.top()->GetId(), EventDestination::SCENE);
		EventManager::GetInstance()->NotifyObservers(jEvent->GetType(), jEvent);
	}
	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_C))
	{
		std::cout << "CHANGING SCENE" << std::endl;
		QueueScene("0");
	}
	if (InputManager::GetInstance().IsMouseButtonPressed(OIS::MB_Left))
	{
		std::cout << "MOUSE CLICKED" << std::endl;
		L_MouseEvent * lEvent = new L_MouseEvent(_states.top()->GetId(), EventDestination::SCENE);
		EventManager::GetInstance()->NotifyObservers(lEvent->GetType(), lEvent);

		// tell the gui
		CEGUIUser::GetInstance()->OnMouseReleased(OIS::MB_Left);
	}
	if (InputManager::GetInstance().GetMouseMove()) {

		Ogre::Real mouseX = InputManager::GetInstance().GetMouseCoords().mouseX;
		Ogre::Real mouseY = InputManager::GetInstance().GetMouseCoords().mouseY;

		MouseMoveEvent * mMove = new MouseMoveEvent(mouseX, mouseY, "MouseMove", EventDestination::SCENE);
		EventManager::GetInstance()->NotifyObservers(EventType::EVENT_MOVE_MOUSE, mMove);
	
		CEGUIUser::GetInstance()->UpdateMouseCoords(mouseX, mouseY);

	}

}


void Game::Update()
{
}

void Game::MessagePump()
{
	MSG  msg;
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Game::UpdateInput()
{
	InputManager::GetInstance().CaptureInput();
	CEGUIUser::GetInstance()->UpdateTime(_deltaTime);
}

void Game::Render()
{
	MyOgre::GetInstance().Render();

	// render gui
	CEGUIUser::GetInstance()->Draw();

	std::cout << "RENDEEEEEEEEEEEEEEEEEEEEEEEER--------------------------->" << std::endl;
}

void Game::ChangeScene(std::string name)
{

	std::cout << "CHANGE SCENEEEEEE" << std::endl;

	// if the stack is not empty (i.e., already has an scene)
	if (!_states.empty()) 
	{
		// delete the current GUI
		CEGUIUser::GetInstance()->Destroy();

		// save the scene in a temp variable
		Scene* aux = _states.top();

		// delete that scene from the stack
		_states.pop();

		// delete pointer to the scene
		delete aux;
	}

	// clear the scene in order to create a new one
	MyOgre::GetInstance().ClearScene();

	// set up cegui scene
	CEGUIUser::GetInstance()->SetUpScene();
	CEGUIUser::GetInstance()->SetFont("DejaVuSans-10");
	CEGUIUser::GetInstance()->SetCursor("AlfiskoSkin");

	// create new scene
	Scene* newScene = new Scene(name, _compFactory);

	// push it to the stack
	_states.push(newScene);

	// set the scene with ogre

	// set flag to false
	_change = false;
}

void Game::QueueScene(std::string scene)
{
	_change = true;
	_nextScene = scene;
}

void Game::ExitGame()
{
	_exit = true;
}

void Game::RegisterComponents()
{
	_compFactory.Register("TransformComponent", new DerivedCreator<TransformComponent, Component>());
	_compFactory.Register("HealthComponent", new DerivedCreator<HealthComponent, Component>());
	_compFactory.Register("RenderComponent", new DerivedCreator<RenderComponent, Component>());
	_compFactory.Register("PlayerControllerComponent", new DerivedCreator<PlayerControllerComponent, Component>());
	_compFactory.Register("RigidBodyComponent", new DerivedCreator<RigidBodyComponent, Component>());
	_compFactory.Register("ButtonComponent", new DerivedCreator<ButtonComponent, Component>());
	_compFactory.Register("ExitButtonComponent", new DerivedCreator<ExitButtonComponent, Component>());
	_compFactory.Register("PathFindingComponent", new DerivedCreator<PathFindingComponent, Component>());
	_compFactory.Register("BulletComponent", new DerivedCreator<BulletComponent, Component>());
}