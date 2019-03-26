#ifndef _H_HEALTHCOMPONENT_H_
#define _H_HEALTHCOMPONENT_H_

#include <../Engine/Component.h>
#include "RIPOEvent.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(std::string id, Entity* e, int health);
	~HealthComponent();

	void virtual OnEvent(Event e);
	void virtual Update();

private:
	int _health;

	void DecreaseHealth();
	void CheckHealth();
};
#endif
