#ifndef MYPHYSX_H
#define MYPHYSX_H

#include <PxPhysicsAPI.h>

// Static variable for the singleton



class MyPhysX
{
private:
	physx::PxPhysics*				gPxPhysics;
	physx::PxFoundation*			gPxFoundation;
	physx::PxCooking*				gPxCooking;
	physx::PxDefaultAllocator		gAllocator;
	physx::PxDefaultErrorCallback   gErrorCallback;

	physx::PxPvd*                           gPvd;
	//physx::PxPvdTransport*				gTransport = NULL;
	physx::PxPvdInstrumentationFlags        gPvdFlags;


	static MyPhysX * _instance;

public:
	MyPhysX();
	~MyPhysX();

	void initPhysX();

	static MyPhysX& GetInstance();

	static void ResetInstance();

	void Shutdown();
};
#endif
