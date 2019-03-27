#ifndef SCENE_H
#define SCENE_H

#include "../Engine/EntityManager.h"
#include "../Engine/FileReader.h"
#include "../Engine/factory.h"


class Scene
{
private: 


	EntityManager* _instanceEM;
	FileReader* _instanceFR;
	std::string _sceneID;
	Factory<Component, std::string> _factory;

public:
	Scene(std::string ID, Factory<Component, std::string> factory);
	~Scene();

	void CreateSceneEntities(nlohmann::json scene);


	void Update();

};
#endif
