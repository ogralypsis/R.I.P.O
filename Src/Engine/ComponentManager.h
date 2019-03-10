#ifndef _H_COMPONENTMANAGER_H_
#define _H_COMPONENTMANAGER_H_
 
#include <Component.h>
#include <map>
#include <string>
#include <vector>
using namespace std;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();
	
	template <class T>
	void AddComponent(T* c);

	void Update();
	
	template <class T>
	T* GetComponent(T* c);

protected:
	

	vector<Component*> _components;
	
};

#endif 
