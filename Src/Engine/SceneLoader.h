#ifndef H_SCENELOADER_H
#define H_SCENELOADER_H

#include "json.hpp"
#include "factory.h"
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