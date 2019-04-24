#include "ButtonComponent.h"
#include <CEGUIUser.h>

ButtonComponent::ButtonComponent() {}

ButtonComponent::~ButtonComponent() {}

void ButtonComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	std::string _nameButton = arguments["name"].str;
	
	// arguments for position of button
	float _posX = arguments["posX"].f;
	float _posOffsetX = arguments["posOffsetX"].f;

	float _posY = arguments["posY"].f;
	float _posOffsetY = arguments["posOffsetY"].f;

	// arguments for size of button
	float _scaleX = arguments["scaleX"].f;
	float _scaleOffsetX = arguments["scaleOffsetX"].f;

	float _scaleY = arguments["scaleY"].f;
	float _scaleOffsetY = arguments["scaleOffsetY"].f;

	//CEGUIUser::GetInstance();
	// call function to create button
	/*CEGUIUser::GetInstance()->CreateButton(_nameButton, 
		CEGUI::UVector2(CEGUI::UDim(_posX, _posOffsetX), CEGUI::UDim(_posY, _posOffsetY)),
		CEGUI::USize(CEGUI::UDim(_scaleX, _scaleOffsetX), CEGUI::UDim(_scaleY, _scaleOffsetY)));
		*/
}

void ButtonComponent::OnEvent(int eventType, Event e)
{
}

void ButtonComponent::Update()
{
}
