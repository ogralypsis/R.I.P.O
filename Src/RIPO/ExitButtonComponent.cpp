#include "ExitButtonComponent.h"

#include "Game.h"

ExitButtonComponent::ExitButtonComponent()
{
}


ExitButtonComponent::~ExitButtonComponent()
{
}

void ExitButtonComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	// type and name
	std::string type = arguments["type"].str;
	std::string name = arguments["name"].str;
	std::string text = arguments["text"].str;

	// arguments for position of button
	float destRectPercX = arguments["destRectPercX"].f;
	float destRectPercY = arguments["destRectPercY"].f;
	float destRectPercZ = arguments["destRectPercZ"].f;
	float destRectPercW = arguments["destRectPercW"].f;

	// arguments for size of button
	float destRectPix = arguments["destRectPix"].f;

	// call function to create button
	CEGUI::PushButton* _button = static_cast<CEGUI::PushButton*>(CEGUIUser::GetInstance()->CreateWidget(type,
		glm::vec4(destRectPercX, destRectPercY, destRectPercZ, destRectPercW), glm::vec4(destRectPix), text, name));

	// subscribe button to click event
	_button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ExitButtonComponent::onGUIEvent, this));
}

bool ExitButtonComponent::onGUIEvent(const CEGUI::EventArgs & arg)
{
	Game::GetInstance().ExitGame();
	return false;
}

void ExitButtonComponent::OnEvent(int eventType, Event e)
{
}

void ExitButtonComponent::Update()
{
}
