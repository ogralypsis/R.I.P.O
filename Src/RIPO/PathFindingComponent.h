#ifndef _H_PATHFINDINGCOMPONENT_H_
#define _H_PATHFINDINGCOMPONENT_H_

#include <Component.h>
#include <MyOgre.h>
#include "TransformComponent.h"
#include "RIPOEvent.h"

class PathFindingComponent : public Component
{
public:
	PathFindingComponent();
	~PathFindingComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);

private:
	// position of the player
	float _playerX;
	float _playerY;
	float _playerZ;

	Ogre::Vector3 _actualTranslateVect;
	Ogre::Quaternion _actualOrientation;
	Dir _negativeDir;
};
#endif
