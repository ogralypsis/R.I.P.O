#ifndef MYPHYSX_H
#define MYPHYSX_H

#include <PxPhysicsAPI.h>



class MyPhysX
{
private:

	//
	physx::PxPhysics*				gPxPhysics;
	physx::PxFoundation*			gPxFoundation;
	physx::PxCooking*				gPxCooking;
	physx::PxDefaultAllocator		gAllocator;
	physx::PxDefaultErrorCallback   gErrorCallback;

	physx::PxPvd*                           gPvd;
	//physx::PxPvdTransport*                  gTransport = NULL;
	physx::PxPvdInstrumentationFlags        gPvdFlags;


public:
	MyPhysX();
	~MyPhysX();

	void initPhysX();


};
#endif
