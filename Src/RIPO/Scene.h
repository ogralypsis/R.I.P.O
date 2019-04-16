#ifndef SCENE_H
#define SCENE_H

#include <factory.h>
#include <Component.h>

class Scene
{
public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	void Update();

private:
	void AddSceneObservers();
};
#endif
