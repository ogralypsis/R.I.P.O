#include "MyPhysX.h"
#include <iostream>

MyPhysX * MyPhysX::_instance = nullptr;

MyPhysX::MyPhysX() {

	_PxPhysics = nullptr;
	_PxFoundation = nullptr;
	_PxCooking = nullptr;
	_Pvd = nullptr;
	_scene = nullptr;
	_dispatcher = nullptr;	
}

MyPhysX::~MyPhysX()
{


}

bool MyPhysX::Init()
{
	_PvdFlags = physx::PxPvdInstrumentationFlag::eDEBUG;

	//SDK	
	_PxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, _Allocator, _ErrorCallback);
	if (_PxFoundation == NULL)	{	
#ifdef _DEBUG
		std::cout << "PxCreateFoundation failed!" << std::endl;
#endif
		return false;
	}


	//gTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	/*
	#if ENABLE_PVD
	_Pvd = physx::PxCreatePvd(*gPxFoundation);
	//_Pvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::eALL);
	_Pvd->connect(*gTransport, physx::PxPvdInstrumentationFlag::ePROFILE);
	#endif
	*/
	
	_PxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *_PxFoundation, physx::PxTolerancesScale(), false, _Pvd);
	if (_PxPhysics == NULL) {
#ifdef _DEBUG
		std::cout << "PxCreatePhysics failed!" << std::endl;
#endif
		return false;
	}

	physx::PxCookingParams params(_PxPhysics->getTolerancesScale());
	params.buildGPUData = true;
	_PxCooking = PxCreateCooking(PX_PHYSICS_VERSION, *_PxFoundation, params);

	if (_PxCooking == NULL) {
#ifdef _DEBUG
		std::cout << "PxCreateCooking failed!" << std::endl;
#endif
	return false;
}

	PxInitExtensions(*_PxPhysics, _Pvd);

	return true;

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
	PxCloseExtensions();

	_PxPhysics->release();	
	_PxCooking->release();
//#if ENABLE_PVD
	//_Pvd->release();
//#endif
	_PxFoundation->release();
}

void MyPhysX::CreateScene()
{

	physx::PxSceneDesc sceneDesc = physx::PxSceneDesc(_PxPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	_dispatcher = physx::PxDefaultCpuDispatcherCreate(0);
	sceneDesc.cpuDispatcher = _dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	_scene = _PxPhysics->createScene(sceneDesc);

}

void MyPhysX::ClearScene()
{
	_dispatcher->release();
	_scene->release();
}

physx::PxScene * MyPhysX::GetScene()
{
	return _scene;
}

void MyPhysX::StepPhysics(float t)
{

	//... pre - simulation work(update controllers, etc) ...
	_scene->simulate(t);
	_scene->fetchResults(true);
	//... post simulation work(process physics events, etc) ...	

	//std::cout << "SIMULATING PHYSX..." << std::endl;
}

physx::PxPhysics * MyPhysX::GetPhysics()
{
	return _PxPhysics;
}





