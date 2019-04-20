#ifndef _H_CAMERAMANAGER_H_
#define _H_CAMERAMANAGER_H_

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <Ogre.h>
#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include "InputManager.h"

class CameraManager : public Ogre::FrameListener
{
public:
	~CameraManager();

	void CreateFPSCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	static CameraManager& GetInstance();

	static void ResetInstance();

	void MoveForward(Ogre::Real time);
	void MoveBack(Ogre::Real time);
	void MoveRight(Ogre::Real time);
	void MoveLeft(Ogre::Real time);

	void FPSrotation(Ogre::Real time);

	virtual bool frameStarted(const Ogre::FrameEvent& e);

private:
	CameraManager();

	static CameraManager* _instance;

	Ogre::SceneNode* _player = nullptr;

	Ogre::Camera* _mainCamera = nullptr;
	Ogre::SceneNode* _camNode = nullptr;
	Ogre::SceneNode* _camYawNode = nullptr;
	Ogre::SceneNode* _camPitchNode = nullptr;
	Ogre::Camera* _camera = nullptr;
	Ogre::Viewport * _viewPort = nullptr;

	mouseCoordinates oldMouseCoords;
	mouseCoordinates newMouseCoords;

	Ogre::Real _rotate;
	Ogre::Real _move;
	Ogre::Vector3 _direction;

	Ogre::Real _speed = 20.0;

};


#endif // 
