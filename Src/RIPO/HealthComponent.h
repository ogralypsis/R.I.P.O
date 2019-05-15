#ifndef _H_HEALTHCOMPONENT_H_
#define _H_HEALTHCOMPONENT_H_
#include <Component.h>

class HealthComponent : public Component
{
public:
	HealthComponent();
	~HealthComponent();

	///<sumary>
	/// initializes the Health component by setting the _ownerEntity and storing the health of the entity (spcified in the Json file)
	///<sumary>
	///<param name="arguments"> arguments read from the Json -> the health of the entity </param>
	///<param name="e"> entity to which the component is attached </param>
	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	///<sumary>
	/// called everytime there an event the component is subscribed to (JEvent and CollisionEvent)
	/// it calls the decrease of health
	///<sumary>
	///<param name="eventType"> type of the event. Necessary in case the component is subscribed to more than one </param>
	///<param name="e"> event with all the info of said event </param>
	void virtual OnEvent(int eventType, Event * e);

	///<sumary>
	/// updates the component
	///<sumary>
	///<param name="deltaTime"> time that has passed since function was last called </param>
	void virtual Update(float deltaTime);

private:
	///<sumary>
	/// number of health the entity has
	///<sumary>
	int _health;

	///<sumary>
	/// lowers the number of health of the entity by a set number (5)
	///<sumary>
	void DecreaseHealth();

	///<sumary>
	/// checks whether the entity still has health, if not, sends an event of death to the entity attached
	///<sumary>
	void CheckHealth();
};
#endif
