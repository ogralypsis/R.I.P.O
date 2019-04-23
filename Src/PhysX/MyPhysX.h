#ifndef MYPHYSX_H
#define MYPHYSX_H

#include <PxPhysicsAPI.h>

class MyPhysX
{
private:

	physx::PxPhysics * _PxPhysics;
	physx::PxFoundation * _PxFoundation;
	physx::PxCooking * _PxCooking;
	physx::PxDefaultAllocator _Allocator;
	physx::PxDefaultErrorCallback _ErrorCallback;

	physx::PxPvd *  _Pvd;
	physx::PxPvdInstrumentationFlags _PvdFlags;
	//physx::PxPvdTransport*				gTransport = NULL;


	static MyPhysX * _instance;
	
	physx::PxScene * _scene;
	physx::PxDefaultCpuDispatcher * _dispatcher;

public:

	MyPhysX();
	~MyPhysX();


	static MyPhysX& GetInstance();

	static void ResetInstance();

	/// <summary>
	/// Initialize PhysX and all necesary resources
	/// </summary>
	bool Init();

	/// <summary>
	/// Release all PhysX objects and resources
	/// </summary>
	void Shutdown();

	void CreateScene();

	void ClearScene();

	void StepPhysics(float t);

	physx::PxPhysics * GetPhysics();
};
#endif
