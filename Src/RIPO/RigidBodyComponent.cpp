#include "RigidBodyComponent.h"
#include <iostream>
#include "RIPOEvent.h"

using namespace physx;
RigidBodyComponent::RigidBodyComponent()
{
	_shape = nullptr;
	_actor = nullptr;
	_material = nullptr;
	_transform = nullptr;
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;
	_id = "RigidBody";

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent("Transform"));

	_mustMove = false;

	// 1: sphere, 2: box, 3: capsule, 4: plane
	int geometry = arguments["geometry"].i;

	float tam1 = arguments["tam1"].f;
	float tam2 = arguments["tam2"].f;
	float tam3 = arguments["tam3"].f;

	_material = MyPhysX::GetInstance().GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f); // static friction, dynamic friction,// restitution

	if (!_material)
#ifdef _DEBUG
		std::cout << "createMaterial failed!" << std::endl;
#endif

	_actor = MyPhysX::GetInstance().GetPhysics()->createRigidDynamic(PxTransform(0, 0, 0));//aqui iria la posicion de la entidad 

	switch (geometry)
	{
	// 1: sphere
	case 1:		
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxSphereGeometry(tam1), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape);

		break;
	// 2: box
	case 2:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxBoxGeometry(tam1/2, tam2/2, tam3/2), *_material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	// 3: capsule
	case 3:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxCapsuleGeometry(tam1, tam2/2), *_material, true); // TODO: mirar flags para colisiones...
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
}

void RigidBodyComponent::OnEvent(int eventType, Event * e)
{
	if (_ownerEntity->GetId() == e->GetEmmitter()) {
		if (eventType == EventType::EVENT_UPDATE_TRANSFORM) {
			_mustMove = true;
			_auxPosX = static_cast<UpdateTransformEvent*>(e)->_posX;
			_auxPosY = static_cast<UpdateTransformEvent*>(e)->_posY;
			_auxPosZ = static_cast<UpdateTransformEvent*>(e)->_posZ;
		}
	}

}

void RigidBodyComponent::Update(float deltaTime)
{
	if (_transform != nullptr && _mustMove == true) {
		_actor->setGlobalPose(PxTransform(_auxPosX,
			_auxPosY,
			_auxPosZ/*,
			PxQuat(_transform->GetRotX(), _transform->GetRotY(), _transform->GetRotZ(), 0.0f)*/));

		_mustMove = false;

		std::cout << "POS Z: " << _transform->GetPosZ() << std::endl;

		std::cout << "POS Y: " << _transform->GetPosY() << std::endl;
	}
}
