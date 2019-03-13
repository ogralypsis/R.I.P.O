#ifndef _H_HEALTHCOMPONENT_H_
#define _H_HEALTHCOMPONENT_H_

#include <../Engine/Component.h>

class HealthComponent : public Component
{
public:
	HealthComponent(std::string id, Entity* e, int health);
	~HealthComponent();

	virtual void OnEvent();

	void DecreaseHealth();
	void CheckHealth();

private:
	int _health;
};
#endif
