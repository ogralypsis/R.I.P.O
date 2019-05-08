#ifndef _H_PATHFINDINGCOMPONENT_H_
#define _H_PATHFINDINGCOMPONENT_H_

#include <Component.h>

class PathFindingComponent : Component
{
public:
	PathFindingComponent();
	~PathFindingComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);

	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);
};
#endif
