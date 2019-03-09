#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "../Ogre/MyOgre.h"

using namespace std;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	
	// For testing, later change for Game game->Init() where must be all libraries initialization...
	MyOgre * ogre = new MyOgre();

	ogre->InitOgre();
	ogre->Shutdown();

	delete ogre;
	ogre = nullptr;


	return 0;
}