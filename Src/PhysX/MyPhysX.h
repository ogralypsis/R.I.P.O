#ifndef MYPHYSX_H
#define MYPHYSX_H

#include <PxPhysicsAPI.h>
#include "callbacks.h"

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
	physx::PxPvdTransport*				gTransport = NULL;
	physx::PxPvdSceneClient* pvdClient;

	static MyPhysX * _instance;
	
	physx::PxScene * _scene;
	physx::PxDefaultCpuDispatcher * _dispatcher;
	ContactReportCallback gContactReportCallback;
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

	physx::PxScene * GetScene();

	void StepPhysics(float t);

	physx::PxPhysics * GetPhysics();
};
#endif
