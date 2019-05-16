#include "callbacks.h"

extern void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);


physx::PxFilterFlags contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
	physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
	physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
		| physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
		| physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return physx::PxFilterFlag::eDEFAULT;
}

void ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	PX_UNUSED(pairs);
	PX_UNUSED(nbPairs);
	physx::PxActor* actor1 = pairHeader.actors[0];
	physx::PxActor* actor2 = pairHeader.actors[1];
	


	onCollision(actor1, actor2);
}
/*void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	//std::cout << "algocolisionaXD" << endl;
};
ContactReportCallback gContactReportCallback;

sceneDesc.filterShader = contactReportFilterShader;
	//
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
*/

/*
*{
	PX_UNUSED(pairs);
	PX_UNUSED(nbPairs);
	/*physx::PxRigidActor* actor1 = pairHeader.actors[0];
	physx::PxRigidActor* actor2 = pairHeader.actors[1];
PxRigidDynamic* act1 = pairHeader.actors[0]->is<PxRigidDynamic>();
PxRigidDynamic* act2 = pairHeader.actors[1]->is<PxRigidDynamic>();
//PxRigidStatic* act4 = pairHeader.actors[1]->is<PxRigidStatic>();
/*if(pairHeader.actors[0]->is<physx::PxRigidDynamic>() && pairHeader.actors[1]->is<physx::PxRigidStatic>())
	onCollision(actor1, actor2);*/

/*if (act1 && act2) {
	onCollision(act1, act2);
}*/
/*if ((act2 && act3)) {
	onCollision(act2, act3);
}
*/
/*
if (player->getBody()->getWorldBounds().intersects(body->getBody()->getWorldBounds())) {
							player->playerDead();
}

*/