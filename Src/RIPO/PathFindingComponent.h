#ifndef _H_PATHFINDINGCOMPONENT_H_
#define _H_PATHFINDINGCOMPONENT_H_

#include <Component.h>

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
};
#endif
