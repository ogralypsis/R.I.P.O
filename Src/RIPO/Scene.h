#ifndef SCENE_H
#define SCENE_H

#include <Factory.h>
#include <Component.h>

class Scene
{
public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	void Update(float t);

private:

	void AddSceneObservers();
		

};
#endif
