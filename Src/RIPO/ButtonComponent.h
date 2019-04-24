#ifndef _H_BUTTONCOMPONENT_H_
#define _H_BUTTONOMPONENT_H_

#include <Component.h>

class ButtonComponent : public Component
{
public:
	ButtonComponent();
	~ButtonComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event e);
	void virtual Update();

private:

};
#endif
