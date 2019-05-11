#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <Component.h>
#include "TransformComponent.h"

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
	//Ogre::SceneNode* GetNode();
	std::vector<int> GetPosition();
	
private:

	//TransformComponent * _transform = nullptr;

	//Ogre::SceneNode* _entityNode = nullptr;
	Ogre::Entity * _entityOgre;


	bool _mustMove;
	bool _mustRotate;

	int _positionX;
	int _positionY;
	int _positionZ;

	float _auxPosX;
	float _auxPosY;
	float _auxPosZ;


	float _rotX;
	float _rotY;

};

#endif RENDER_COMPONENT_H
