#include "BaseScene.h"

BaseScene::BaseScene(std::string id, Factory<Component> compFactory) : _id(id) {}

BaseScene::~BaseScene() {}
