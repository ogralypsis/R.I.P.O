#include "RigidBodyComponent.h"
#include <iostream>


using namespace physx;
RigidBodyComponent::RigidBodyComponent()
{
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Init(std::map<std::string, Arguments> arguments, Entity * e)
{
	_ownerEntity = e;

	_transform = dynamic_cast<TransformComponent*>(_ownerEntity->GetComponent(_transform));

	// 1: sphere, 2: box, 3: capsule, 4: plane
	int geometry = arguments["geometry"].i;

	float tam1 = arguments["tam1"].f;
	float tam2 = arguments["tam2"].f;
	float tam3 = arguments["tam3"].f;

	const physx::PxMaterial * material = MyPhysX::GetInstance().GetPhysics()->createMaterial(0.5f, 0.5f, 0.1f); // static friction, dynamic friction,// restitution

	if (!material)
#ifdef _DEBUG
		std::cout << "createMaterial failed!" << std::endl;
#endif

	_actor = MyPhysX::GetInstance().GetPhysics()->createRigidDynamic(PxTransform(0, 0, 0));//aqui iria la posicion de la entidad 

	switch (geometry)
	{
	// 1: sphere
	case 1:		
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxSphereGeometry(tam1), *material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape);

		break;
	// 2: box
	case 2:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxBoxGeometry(tam1/2, tam2/2, tam3/2), *material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	// 3: capsule
	case 3:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxCapsuleGeometry(tam1, tam2/2), *material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	// 4: plane
	case 4:
		_shape = MyPhysX::GetInstance().GetPhysics()->createShape(PxPlaneGeometry(), *material, true); // TODO: mirar flags para colisiones...
		_actor->attachShape(*_shape); 
		break;
	default:
		break;
	}
	
	MyPhysX::GetInstance().GetScene()->addActor(*_actor);
}

void RigidBodyComponent::OnEvent(int eventType, Event e)
{
	//Para el player:




}

void RigidBodyComponent::Update(float deltaTime)
{
	
	_actor->setGlobalPose(PxTransform(_transform->GetPosX(),
										_transform->GetPosY(), 
											_transform->GetPosZ(),
		PxQuat(_transform->GetRotX(),_transform->GetRotY(),_transform->GetRotZ(),0.0f)));



}
