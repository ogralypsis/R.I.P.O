#ifndef SCENE_H
#define SCENE_H

#include <BaseScene.h>

class Scene : public BaseScene
{
public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	virtual void Update(float t);

private:

	virtual void AddSceneObservers();
		
	// Identifier for the scene created
	std::string _id;

};
#endif
