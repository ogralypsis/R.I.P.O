#include "Component.h"

Component::Component() {}

Component::~Component() {}

std::string Component::GetId()
{
	return _id;
}

std::string Component::GetOwnerEntId()
{
	return _ownerEntity->GetId();
}

std::map<std::string, Arguments> Component::GetArguments()
{
	return _originalArguments;
}
