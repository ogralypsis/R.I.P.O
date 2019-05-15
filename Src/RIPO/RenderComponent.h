#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <Component.h>
#include "TransformComponent.h"


#include "Utils.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void virtual Init(std::map<std::string, Arguments> arguments, Entity* e);
	void virtual OnEvent(int eventType, Event * e);
	void virtual Update(float deltaTime);

	void GetEntitySize();

	//returns the entities SceneNode
	Ogre::SceneNode* GetNode();
	
	Pos GetPosition();

	Quat GetOrientation();
	
private:

	

	Ogre::Entity * _entityOgre;


	bool _mustMove;
	bool _mustRotate;

	float _positionX;
	float _positionY;
	float _positionZ;

	float _auxPosX;
	float _auxPosY;
	float _auxPosZ;
};

#endif RENDER_COMPONENT_H
