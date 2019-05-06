#ifndef _H_BUTTONCOMPONENT_H_
#define _H_BUTTONOMPONENT_H_

#include <Component.h>

// singleton
#include <CEGUIUser.h>

class ButtonComponent : public Component
{
public:
	ButtonComponent();
	~ButtonComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	bool onGUIEvent(const CEGUI::EventArgs & arg);

	void virtual OnEvent(int eventType, Event  * e);
	void virtual Update(float deltaTime);

private:
	std::string _nextScene;
};
#endif
