#ifndef _H_CAMERAMANAGER_H_
#define _H_CAMERAMANAGER_H_

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <Ogre.h>
#include <OgreRenderWindow.h>
#include "InputManager.h"


class CameraManager 
{
public:
	~CameraManager();

	void CreateCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	static CameraManager& GetInstance();

	static void ResetInstance();
	
	
	///<sumary>
	///Movement methods to be called from a PlayerController
	///Moves a SceneNode different to _camNode
	///<sumary>
	/*void MoveForward(Ogre::Real time);
	void MoveBack(Ogre::Real time);
	void MoveRight(Ogre::Real time);
	void MoveLeft(Ogre::Real time);*/


	///<sumary>
	///To be called from a PlayerController, rotates the camara SceneNode
	///<sumary>
	void FPSrotation(float time, Ogre::Real mouseX, Ogre::Real mouseY);

	///<sumary>
	///To be called from a PlayerController, attaches the camera node to a node
	///<sumary>
	void AttachPlayer(Ogre::SceneNode* playerNode);


	float GetRotX() { return _rotX; }
	float GetRotY() { return _rotY; }


private:

	CameraManager();

	static CameraManager* _instance;

	//TESTING: AUXILIAR NODE -> TO BE CHANGED
	Ogre::SceneNode* _player = nullptr;

	//attributes for FPSrotation
	Ogre::Real _rotX;
	Ogre::Real _rotY;
	Ogre::Real _rotSpeed = 5;
	Ogre::Real _maxPitch = 30;

	Ogre::Real _speed = 5.0;

	Ogre::Camera* _mainCamera = nullptr;
	Ogre::SceneNode* _camNode = nullptr;
	Ogre::SceneNode* _camYawNode = nullptr;
	Ogre::SceneNode* _camPitchNode = nullptr;
	Ogre::Camera* _camera = nullptr;
	Ogre::Viewport * _viewPort = nullptr;
	

};


#endif // 
