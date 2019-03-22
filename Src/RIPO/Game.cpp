#include "Game.h"
#include "../Ogre/MyOgre.h"
#include "../PhysX/MyPhysX.h"
#include "../Engine/EventManager.h"
#include "HealthComponent.h"

#include <Windows.h>

// Static variable for the singleton
Game * Game::_instance = nullptr;

Game::Game()
{	
	// For testing, delete later 
	MyPhysX * mp =  new MyPhysX();
	// ------------------------
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

	// TESTING DELETE LATER
	MyOgre::GetInstance().CreateSinBad();

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

	/*while (true) {

		std::cout << "loop" << std::endl;
		Sleep(10000);
	}*/
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
}

void Game::RegisterComponents()
{
	//Factory<Component, std::string>::getInstance()->Register("HealthComponent", new DerivedCreator<HealthComponent, Component>());

	compFactory.Register("HealthComponent", new DerivedCreator<HealthComponent, Component>());
}