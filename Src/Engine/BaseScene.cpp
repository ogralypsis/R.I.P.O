#include "BaseScene.h"

BaseScene::BaseScene(std::string id, Factory<Component> compFactory) : _id(id) {}

BaseScene::~BaseScene() {}

std::string BaseScene::GetId()
{
	return _id;
}
