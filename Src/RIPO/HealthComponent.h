#ifndef _H_HEALTHCOMPONENT_H_
#define _H_HEALTHCOMPONENT_H_

#include <Component.h>

class HealthComponent : public Component
{
public:
	HealthComponent();
	~HealthComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event e);
	void virtual Update(float deltaTime);

private:
	int _health;

	void DecreaseHealth();
	void CheckHealth();
};
#endif
