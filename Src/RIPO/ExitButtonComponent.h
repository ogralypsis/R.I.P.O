#pragma once

#include <Component.h>

// singleton
#include <CEGUIUser.h>

class ExitButtonComponent : public Component
{
public:
	ExitButtonComponent();
	~ExitButtonComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	bool onGUIEvent(const CEGUI::EventArgs & arg);

	void virtual OnEvent(int eventType, Event e);
	void virtual Update();
private:

};

