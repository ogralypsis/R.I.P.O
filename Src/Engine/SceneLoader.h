#ifndef H_SCENELOADER_H
#define H_SCENELOADER_H
/*
SINGLETON THAT LOADS THE SCENE SPECIFIED IN THE JSON THAT FILEREADER READS
IT CREATES THE COMPONENTS, ENITITIES, EVENTS
CALLED FROM THE SCENE
*/
#include "Factory.h"
#include "Component.h"

class SceneLoader
{
public:
	~SceneLoader();

	static SceneLoader* getInstance();

	void LoadFromJson(nlohmann::json _json, Factory<Component>);

private:
	SceneLoader();

	static SceneLoader* _instance;
};
#endif