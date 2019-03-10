#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "Game.h"

using namespace std;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks


	if (Game::GetInstance().Init()) {
		Game::GetInstance().Loop();
		Game::GetInstance().Release();
	}
	else {
#ifdef _DEBUG
		std::cout << "Something failed at Game's initialization" << std::endl;
#endif		
	}
	Game::ResetInstance();

	return 0;
}