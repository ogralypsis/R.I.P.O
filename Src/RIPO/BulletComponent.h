#ifndef _H_BULLECOMPONENT_H_
#define _H_BULLECOMPONENT_H_

#include <Component.h>

class BulletComponent : public Component
{
public:
	BulletComponent();
	
	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);

	~BulletComponent();

private: 
	float _speed; 
	
};

#endif // !_H_BULLECOMPONENT_H_
