#pragma once
#include <Component.h>
#include <MyPhysX.h>

class RigidBodyComponent :
	public Component
{
public:
	RigidBodyComponent();
	~RigidBodyComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event e);

	void virtual Update();

private:

	physx::PxShape * _shape;
	physx::PxActor *_actor;
};

