#ifndef SCENE_H
#define SCENE_H

#include "../Engine/EntityManager.h"
#include "../Engine/FileReader.h"



class Scene
{
private: 


	EntityManager* _instanceEM;
	FileReader* _instanceFR;
	std::string _sceneID;

public:
	Scene(std::string ID);
	~Scene();

	void CreateSceneEntities(nlohmann::json scene);


	void Update();

};
#endif
