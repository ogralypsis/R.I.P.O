#include "MyPhysX.h"

MyPhysX * MyPhysX::_instance = nullptr;


MyPhysX::MyPhysX() {
	gPxPhysics = NULL;
	gPxFoundation = NULL;
	gPxCooking = NULL;
	gPvd = NULL;
	
}

void MyPhysX::initPhysX()
{
	gPvdFlags = physx::PxPvdInstrumentationFlag::eDEBUG;

	//SDK
	gPxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gPxFoundation, physx::PxTolerancesScale(), false, gPvd);

	//gTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

#if ENABLE_PVD
	gPvd = physx::PxCreatePvd(*gPxFoundation);
	//gPvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::eALL);
	gPvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::ePROFILE);
#endif

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

MyPhysX & MyPhysX::GetInstance()
{	
	if (MyPhysX::_instance == nullptr)
		MyPhysX::_instance = new MyPhysX();

	return *MyPhysX::_instance;
}

void MyPhysX::ResetInstance()
{
	if (_instance != nullptr) {
		delete MyPhysX::_instance;
		MyPhysX::_instance = nullptr;
	}
}

void MyPhysX::Shutdown()
{


}

MyPhysX::~MyPhysX()
{


}