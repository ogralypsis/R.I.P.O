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
	_newTime = 0;
	_frameTime = _accumulator = _inputTime = 0.0f;
}


Game::~Game()
{
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
		CEGUIUser::GetInstance()->SetFont("DejaVuSans-10");
		CEGUIUser::GetInstance()->SetCursor("AlfiskoSkin");
	}
	
	RegisterComponents();

	ChangeScene("1");

	return true;
}

void Game::Release()
{
	// Release MyOgre
	MyOgre::GetInstance().Shutdown();
	// Delete MyOgre instance
	MyOgre::ResetInstance();
}

void Game::Loop()
{


	// Get the current time in seconds
	time(&_currentTime);

	int frames = 0;


	// Continue the loop if the window is not closed and game is not exited
	while (!MyOgre::GetInstance().CheckWindowStatus() && !_exit) 
	{		
		// Update loop parameters
		time(&_newTime);	
		_frameTime = _newTime - _currentTime;
		_currentTime = _newTime;
		_accumulator += _frameTime;

		MessagePump();

		// Loop for game logic and physics step (60 times per second)
		while (_accumulator >= _FPS_CAP) {

			
			HandleInput();
			
			// INPUT
			// PHYSCS STEP
			// CURRENT SCENE UPDATE

			// ESCENA->UPDATE: physxScene->simulate

			_states.top()->Update(_FPS_CAP);

			_accumulator -= _FPS_CAP;
			frames++;
		}
		
		frames = 0;

		Render();
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

	InputManager::GetInstance().CaptureInput();

	if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_W)) {

		std::cout << "PRESSING KEY W" << std::endl;
	}
	else if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_S))
	{
		std::cout << "PRESSING KEY S" << std::endl;

		// --------------------------------------> TESTING EVENTS NOTIFICATION <--------------------------------------
		UpdateTransformEvent utEvent(0, 0, 0, 0, 0, "Enemy", EventDestination::SCENE); // Emmitter falseado luego ver si seria el id de la escena o game
		EventManager::GetInstance()->NotifyObservers(EventType::EVENT_UPDATE_TRANSFORM, utEvent);
		// -----------------------------------------------------------------------------------------------------------
	}
	else if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_A))
	{

		std::cout << "PRESSING KEY A" << std::endl;
	}
	else if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_D))
	{

		std::cout << "PRESSING KEY D" << std::endl;
	}

	else if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_C))
	{
		std::cout << "CHANGING SCENE" << std::endl;
		ChangeScene("2");
	}

	else if (InputManager::GetInstance().IsMouseButtonPressed(OIS::MB_Left))
	{
		std::cout << "MOUSE CLICKED" << std::endl;
		// tell the gui
		CEGUIUser::GetInstance()->OnMouseReleased(OIS::MB_Left);
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

void Game::Render()
{
	MyOgre::GetInstance().Render();

	// render gui
	//CEGUIUser::GetInstance()->Draw();
}

void Game::ChangeScene(std::string name)
{
	// if the stack is not empty (i.e., already has an scene)
	if (!_states.empty()) 
	{
		// save the scene in a temp variable
		Scene* aux = _states.top();
		// delete that scene from the stack
		_states.pop();
		// delete pointer to the scene
		delete aux;
	}

	// create new scene
	Scene* newScene = new Scene(name, _compFactory);

	// push it to the stack
	_states.push(newScene);
}

void Game::RegisterComponents()
{
	_compFactory.Register("TransformComponent", new DerivedCreator<TransformComponent, Component>());
	_compFactory.Register("HealthComponent", new DerivedCreator<HealthComponent, Component>());
	_compFactory.Register("RenderComponent", new DerivedCreator<RenderComponent, Component>());
	_compFactory.Register("PlayerControllerComponent", new DerivedCreator<PlayerControllerComponent, Component>());
	_compFactory.Register("RigidBodyComponent", new DerivedCreator<RigidBodyComponent, Component>());
	_compFactory.Register("ButtonComponent", new DerivedCreator<ButtonComponent, Component>());

}