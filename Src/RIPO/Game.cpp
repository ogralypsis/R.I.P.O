#include "Game.h"
#include "../Ogre/MyOgre.h"
#include <iostream>


Game::Game()
{
	Init();

}


Game::~Game()
{
}

void Game::Loop()
{
}

bool Game::Init()
{
	if (!MyOgre::GetInstance().InitOgre()) {
		std::cout << "OGRE couldn't be initialized";
		return false;
	}
}

void Game::Release()
{
	// Delete MyOgre instance
	MyOgre::ResetInstance();
}

void Game::HandleInput()
{
}

void Game::Update()
{
}

void Game::Render()
{
}
