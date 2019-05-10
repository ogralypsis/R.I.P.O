#include "RigidBodyComponent.h"
#include <iostream>
#include "RIPOEvent.h"
#include <EventManager.h>

using namespace physx;
RigidBodyComponent::RigidBodyComponent()
{
	_shape = nullptr;
	_actor = nullptr;
	_material = nullptr;
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "RigidBody";

	_mustMove = false;

	// 1: sphere, 2: box, 3: capsule, 4: plane
	int geometry = arguments["geometry"].i;

	 _tam1 = arguments["tam1"].f;
	 _tam2 = arguments["tam2"].f;
	 _tam3 = arguments["tam3"].f;

	//_velocity = arguments["velocity"].f; // TODO: METER PARAMETRO VELOCITY EN EL JSON
	_velocity = 100.0f;

	_material = MyPhysX::GetInstance().GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f); // static friction, dynamic friction,// restitution

	if (!_material)
#ifdef _DEBUG
		std::cout << "createMaterial failed!" << std::endl;
#endif

	_actor = MyPhysX::GetInstance().GetPhysics()->createRigidDynamic(PxTransform(0, 0, 0));//aqui iria la posicion de la entidad 
	_actor->setLinearDamping(0.75f);
	_actor->setMass(10.0f);
	
	switch (geometry)
	{
	// 1: sphere
	case 1:		
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxSphereGeometry(_tam1), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape);

		break;
	// 2: box
	case 2:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxBoxGeometry(_tam1/2, _tam2/2, _tam3/2), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	// 3: capsule
	case 3:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxCapsuleGeometry(_tam1, _tam2/2), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	// 4: plane
	case 4:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxPlaneGeometry(), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	default:
		break;
	}
	
	MyPhysX::GetInstance().GetScene()->addActor(*_actor);

	_shape->release();

	_dir.x = 0;
	_dir.y = 0;
	_dir.z = 0;

}

void RigidBodyComponent::OnEvent(int eventType, Event * e)
{
	
	if (eventType == EventType::EVENT_PHYSICS_MOVE) {
		_mustMove = true;
		_dir.x = static_cast<PhysicsMoveEvent*>(e)->_dir.x;
		_dir.y = static_cast<PhysicsMoveEvent*>(e)->_dir.y;
		_dir.z = static_cast<PhysicsMoveEvent*>(e)->_dir.z;
	}

		
		// SI LLEGA MENSAJE DE QUE TIENE QUE MOVERSE SE APLICA UNA VELOCIDAD (_actor->setLinerVelocity())
		// Y DESPUES MANDAR EL MENSAJE DE EVENT_UPDATE_TRANSFORM QUE DEBERIA LLEGAR AL RENDER Y AL TRANSFORM
		// JUSTO AL REVES CON EL TRANSFORM PORQUE EL QUE ACTUALIZA LAS POSICIONES TIENE QUE SER EL RIGIDBODY 
		// NO EL TRANSFORM NI EL PLAYERCONTROLLER

		

}

void RigidBodyComponent::Update(float deltaTime)
{


	/*
	If required, it is possible to immediately update the velocity of the body using body.setLinearVelocity(body.getLinearVelocity() + deltaLinearVelocity) 
	and body.setAngularVelocity(body.getAngularVelocity() + deltaAngularVelocity)
	*/

	if (!_mustMove) {
		
		_dir = { 0,0,0 };
	
		_actor->addForce(_dir * _velocity * deltaTime, physx::PxForceMode::eIMPULSE);

	}
	else {
		_actor->addForce(_dir * _velocity * deltaTime, physx::PxForceMode::eIMPULSE);
	}

		_transform = _actor->getGlobalPose();

		std::cout << "POS Z: " + _ownerEntity->GetId() + " " << _transform.p.z << std::endl;
		std::cout << "POS Y: " + _ownerEntity->GetId() + " " << _transform.p.y << std::endl;

		UpdateTransformEvent * utEvent = new UpdateTransformEvent(_transform.p.x, _transform.p.y, _transform.p.z, _transform.q.getAngle(), _ownerEntity->GetId(), EventDestination::ENTITY);
		EventManager::GetInstance()->NotifyObservers(utEvent->GetType(), utEvent);

		_mustMove = false;
}
