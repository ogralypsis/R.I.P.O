#include <iostream>


#include "../Ogre/MyOgre.h"

using namespace std;

int main() {

	cout << "HOLA!" << endl;

	MyOgre * ogre = new MyOgre();

	ogre->InitOgre();

	return 0;
}