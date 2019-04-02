#include "Game.h"

#include "../PhysX/MyPhysX.h"

#include "../Ogre/MyOgre.h"
#include "../Ogre/InputManager.h"

#include "../Engine/EventManager.h"
#include "../Engine/Component.h"

#include "RIPOEvent.h"
#include "Scene.h"

#include "HealthComponent.h"
#include "RenderComponent.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"

#include <Windows.h>
#include <time.h>
#include <iostream>


// Static variable for the singleton
Game * Game::_instance = nullptr;

Game::Game()
{	
	// For testing, delete later 
	MyPhysX * mp =  new MyPhysX();
	// ------------------------

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
	if (!MyOgre::GetInstance().InitOgre()) {
#ifdef _DEBUG
		std::cout << "OGRE couldn't be initialized" << std::endl;
#endif
		return false;
	}

	/*
	// TESTING DELETE LATER
	MyOgre::GetInstance().CreateSinBad();
	*/

	if (!InputManager::GetInstance().InitInput(MyOgre::GetInstance().GetWindow()))
		std::cout << "OIS Input system could not be initialized" << std::endl;

	RegisterComponents();

	ChangeScene("data_map1");

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
	
	// Continue the loop if the window is not closed and game is not exited
	while (!MyOgre::GetInstance().CheckWindowStatus() && !_exit) {

		// Get the current time in seconds
		time(&_currentTime);
		//_currentTime = (SDL_GetTicks() / 1000.0);
		int frames = 0;

		/*
		.
		.
		.
		Change scenes if necessary
		.
		.
		.
		*/
		
		
		// Update loop parameters
		time(&_newTime);	
		_frameTime = _newTime - _currentTime;
		_currentTime = _newTime;
		_accumulator += _frameTime;


		//std::cout << "LOOP" << std::endl;
		
		// Loop for game logic and physics step (60 times per second)
		if (_accumulator >= _FPS_CAP) {

			if (InputManager::GetInstance().IsKeyDown(OIS::KeyCode::KC_J))
				std::cout << "PRESSING KEY J" << std::endl;
			else 
				std::cout << "NO INPUT" << std::endl;
			// INPUT
			// PHYSCS STEP
			// CURRENT SCENE UPDATE
		
			_accumulator -= _FPS_CAP;
			frames++;
		}


		
		//std::cout << "loop" << std::endl;
		//Sleep(1000);
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
	// presiona  la tecla "J" y manda un evento de input
	JEvent myEvent(0);
	EventManager::getInstance()->NotifyObservers(myEvent);
}

void Game::Update()
{
}

void Game::Render()
{
	MyOgre::GetInstance().Render();
}

void Game::ChangeScene(std::string name)
{
	Scene* newScene = new Scene(name, _compFactory);
}

void Game::RegisterComponents()
{
	_compFactory.Register("TransformComponent", new DerivedCreator<TransformComponent, Component>());
	_compFactory.Register("HealthComponent", new DerivedCreator<HealthComponent, Component>());
	_compFactory.Register("RenderComponent", new DerivedCreator<RenderComponent, Component>());
	_compFactory.Register("PlayerControllerComponent", new DerivedCreator<PlayerControllerComponent, Component>());
	

}