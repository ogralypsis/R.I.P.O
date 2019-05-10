#include "ExitButtonComponent.h"

#include "Game.h"

ExitButtonComponent::ExitButtonComponent() {}

ExitButtonComponent::~ExitButtonComponent() {}

void ExitButtonComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	// type and name
	std::string type = arguments["type"]._str;
	std::string name = arguments["name"]._str;
	std::string text = arguments["text"]._str;

	// arguments for position of button
	float destRectPercX = arguments["destRectPercX"]._f;
	float destRectPercY = arguments["destRectPercY"]._f;
	float destRectPercZ = arguments["destRectPercZ"]._f;
	float destRectPercW = arguments["destRectPercW"]._f;

	// arguments for size of button
	float destRectPix = arguments["destRectPix"]._f;

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

void ExitButtonComponent::OnEvent(int eventType, Event * e) {}

void ExitButtonComponent::Update(float deltaTime) {}
