#ifndef SCENE_H
#define SCENE_H

#include <factory.h>
#include <Component.h>

#include <MyPhysX.h>

class Scene
{
public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	void Update(float t);

private:

	void AddSceneObservers();
	
	physx::PxRigidStatic* suelo = nullptr;

};
#endif
