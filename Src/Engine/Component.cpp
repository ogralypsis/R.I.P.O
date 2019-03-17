#include "Component.h"

Component::Component(std::string id, Entity* e) : _id(id), _ownerEntity(e) {}

Component::~Component() {}
