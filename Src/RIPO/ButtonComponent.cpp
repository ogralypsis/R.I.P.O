#include "ButtonComponent.h"

#include "Game.h"

ButtonComponent::ButtonComponent() {}

ButtonComponent::~ButtonComponent() {}

void ButtonComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	// type and name
	std::string type = arguments["type"].str;
	std::string name = arguments["name"].str;
	std::string text = arguments["text"].str;
	_nextScene = arguments["scene"].str;

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
	_button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonComponent::onGUIEvent, this));
}

bool ButtonComponent::onGUIEvent(const CEGUI::EventArgs & arg) 
{
	// event "change scene"
	//Game::GetInstance().ChangeScene(_nextScene); // button will take player to game
	printf("%s \n", "I'VE BEEN CLIIiIIIIIIIIICKED");

	return true;
}

void ButtonComponent::OnEvent(int eventType, Event e)
{
}

void ButtonComponent::Update()
{
}
