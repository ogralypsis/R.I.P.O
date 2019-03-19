#ifndef SCENE_H
#define SCENE_H

#include "../Engine/EntityManager.h"
#include <string>
#include "../Engine/factory.h"
#include "HealthComponent.h"



class Scene
{
private: 

	// Factory things
	Factory comp_factory;

#define REGISTER_CLASS(m) comp_factory.register_class<m>(#m)


	EntityManager* instanceEM;
	FileReader* instanceFR;
	std::string _sceneID;

public:
	Scene(std::string ID);
	~Scene();

	void setComponentFactory();
	void CreateSceneEntities(nlohmann::json scene);


	void Update();

};
#endif
