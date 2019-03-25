#ifndef _H_PLAYERCONTROLLERCOMPONENT_H_
#define _H_PLAYERCONTROLLERCOMPONENT_H_

#include <../Engine/Component.h>
#include "RIPOEvent.h"

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent();
	PlayerControllerComponent(std::string id, Entity* e);
	~PlayerControllerComponent();

	void virtual OnEvent(Event e);

	void virtual Update();

private:

	void ForwardMovement();
	void LeftMovement();
	void BackMovement();
	void RightMovement();


	//Internal variables
	int _velocity;
};

#endif