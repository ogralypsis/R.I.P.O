#include "BaseScene.h"




BaseScene::BaseScene(std::string ID, Factory<Component> compFactory)
{
	_id = ID;
}

BaseScene::~BaseScene()
{
}

