#include "BaseScene.h"




BaseScene::BaseScene(std::string ID, Factory<Component> compFactory)
{
	_id = ID;

	json entities = FileReader::getInstance()->readFile("Assets/Maps/Map" + ID + "/" + "data_map" + ID + ".json");

	SceneLoader::getInstance()->LoadFromJson(entities, compFactory);
}

BaseScene::~BaseScene()
{
}

