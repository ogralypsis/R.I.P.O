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
	int geometry = arguments["geometry"]._i;

	_tam1 = arguments["tam1"]._f;
	_tam2 = arguments["tam2"]._f;
	_tam3 = arguments["tam3"]._f;

	_velocity = arguments["velocity"]._f; 

	_render = dynamic_cast<RenderComponent*>(_ownerEntity->GetComponent("Render"));

	_material = MyPhysX::GetInstance().GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f); // static friction, dynamic friction,// restitution

	if (!_material)
#ifdef _DEBUG
		std::cout << "createMaterial failed!" << std::endl;
#endif
	_actor = MyPhysX::GetInstance().GetPhysics()->createRigidDynamic(PxTransform(_render->GetPosition()[0] , _render->GetPosition()[1], _render->GetPosition()[2]));// TODO: aqui iria la posicion de la entidad 
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
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxBoxGeometry(_tam1 / 2, _tam2 / 2, _tam3 / 2), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape);
		break;
		// 3: capsule
	case 3:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxCapsuleGeometry(_tam1, _tam2 / 2), *_material, true); // TODO: mirar flags para colisiones...
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

	/*

	CREAR CUSTOM SHAPE A TRAVES DEL VECTOR DE VERTICES PASADO DEL MESH DE OGRE

	static const PxVec3 convexVerts[] = {PxVec3(0,1,0),PxVec3(1,0,0),PxVec3(-1,0,0),PxVec3(0,0,1),
    PxVec3(0,0,-1)};
Then construct a description of the convex data layout:

PxConvexMeshDesc convexDesc;
convexDesc.points.count     = 5;
convexDesc.points.stride    = sizeof(PxVec3);
convexDesc.points.data      = convexVerts;
convexDesc.flags            = PxConvexFlag::eCOMPUTE_CONVEX;
Now use the cooking library to construct a PxConvexMesh:

PxDefaultMemoryOutputStream buf;
PxConvexMeshCookingResult::Enum result;
if(!cooking.cookConvexMesh(convexDesc, buf, &result))
    return NULL;
PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
PxConvexMesh* convexMesh = physics->createConvexMesh(input);
Finally, create a shape using a PxConvexMeshGeometry which instances the mesh:

PxShape* aConvexShape = aConvexActor->createShape(PxConvexMeshGeometry(convexMesh), aMaterial);

	*/

	_actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	//añadir mas flags pejemplo
	_actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
	_actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
	_actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);



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
	if (eventType == EventType::EVENT_ROTATION) {//cambiar rotacion
		
		_rotX = static_cast<RotationEvent*>(e)->_rotX;
		_rotY = static_cast<RotationEvent*>(e)->_rotY;
	
	}

}
void RigidBodyComponent::Update(float deltaTime)
{

	if (!_mustMove) {

		_dir = { 0,0,0 };

		_actor->addForce(_dir * _velocity * deltaTime, physx::PxForceMode::eIMPULSE);

	}
	else {
		_actor->addForce(_dir * _velocity * deltaTime, physx::PxForceMode::eIMPULSE);
	}

	_transform = _actor->getGlobalPose();

	//std::cout << "POS X: " + _ownerEntity->GetId() + " " << _transform.p.x << std::endl;
	//std::cout << "POS Y: " + _ownerEntity->GetId() + " " << _transform.p.y << std::endl;
	//std::cout << "POS Z: " + _ownerEntity->GetId() + " " << _transform.p.z << std::endl;

	UpdateTransformEvent * utEvent = new UpdateTransformEvent(_transform.p.x, _transform.p.y, _transform.p.z, _transform.q.getAngle(), _ownerEntity->GetId(), EventDestination::SCENE);
	EventManager::GetInstance()->NotifyObservers(utEvent->GetType(), utEvent);

	_mustMove = false;
}


