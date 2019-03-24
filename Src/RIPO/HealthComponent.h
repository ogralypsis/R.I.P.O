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

	void DecreaseHealth();
	void CheckHealth();

private:
	int _health;
};
#endif
