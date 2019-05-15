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
	physx::PxQuat _orientation;

	RenderComponent * _render;

	// Determine if the rigidbody must be updated
	bool _mustMove;
	bool _mustRotate;

	physx::PxVec3 _dir;

	float _rotX;
	float _rotY;


	float _velocity;

	int _geometry;

	float _tam1;
	float _tam2;
	float _tam3;




	physx::PxQuat ModifyAngleAroundAxis(float angle, physx::PxVec3 axis);


};
#endif
