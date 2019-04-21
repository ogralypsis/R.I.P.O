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
	void CreateMainCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	void CreateFPSCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	static CameraManager& GetInstance();

	static void ResetInstance();

	void FPSrotation(Ogre::Real time);

	void CameraMovement(Ogre::Real time);

	virtual bool frameStarted(const Ogre::FrameEvent& e);

private:
	CameraManager();

	static CameraManager* _instance;

	Ogre::Degree _rotX;
	Ogre::Degree _rotY;
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

};


#endif // 
