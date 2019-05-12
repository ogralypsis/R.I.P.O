#ifndef RIGIDBODY_COMPONENT_H_
#define RIGIDBODY_COMPONENT_H_
#include <Component.h>
#include <MyPhysX.h>
#include "RenderComponent.h"

class RigidBodyComponent :
	public Component
{
public:
	RigidBodyComponent();
	~RigidBodyComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event * e);

	void virtual Update(float deltaTime);

private:
	
	physx::PxShape * _shape;
	physx::PxRigidDynamic *_actor;
	const physx::PxMaterial * _material;

	physx::PxTransform  _transform;

	// Determine if the rigidbody must be updated
	bool _mustMove;

	physx::PxVec3 _dir;

	float _rotX;
	float _rotY;


	float _velocity;

	float _tam1;
	float _tam2;
	float _tam3;


	RenderComponent * _render;
};
#endif
