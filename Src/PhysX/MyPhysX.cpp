#include "MyPhysX.h"

#include <PxPhysicsAPI.h>
//#include <PxDefaultErrorCallback.h>
//#include <PxFoundation.h>





MyPhysX::MyPhysX()
{	
	
	// PhysX
	physx::PxPhysics*				gPxPhysics = NULL;
	physx::PxFoundation*			gPxFoundation = NULL;
	physx::PxCooking*				gPxCooking = NULL;
	static physx::PxDefaultAllocator		gAllocator;
	static physx::PxDefaultErrorCallback   gErrorCallback;

	physx::PxPvd*                           gPvd = NULL;
	//physx::PxPvdTransport*                  gTransport = NULL;
	physx::PxPvdInstrumentationFlags        gPvdFlags = physx::PxPvdInstrumentationFlag::eDEBUG;


	// SDK
	gPxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	//gTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

	gPvd = NULL;

#if ENABLE_PVD
	gPvd = physx::PxCreatePvd(*gPxFoundation);
	//gPvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::eALL);
	gPvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::ePROFILE);
#endif

	gPxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gPxFoundation, physx::PxTolerancesScale(), false, gPvd);



	if (gPxPhysics == NULL)
	{
		printf("\nPhysXSDK create error.\nUnable to initialize the PhysX SDK, exiting the sample.\n\n");
		//return false;
	}
	physx::PxCookingParams params(gPxPhysics->getTolerancesScale());
	params.buildGPUData = true;
	gPxCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gPxFoundation, params);

	if (gPxCooking == NULL)
	{
		printf("\nError: Unable to initialize the cooking library, exiting the sample.\n\n");
		//return false;
	}

	PxInitExtensions(*gPxPhysics, gPvd);
}


MyPhysX::~MyPhysX()
{
}

