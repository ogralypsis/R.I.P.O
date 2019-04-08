#ifndef _H_CAMERAMANAGER_H_
#define _H_CAMERAMANAGER_H_

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <Ogre.h>
#include <OgreRenderWindow.h>

class CameraManager
{
public:
	~CameraManager();
	void CreateMainCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	static CameraManager& GetInstance();

	static void ResetInstance();


private:
	CameraManager();

	static CameraManager* _instance;

	Ogre::Camera* _mainCamera = nullptr;
	Ogre::SceneNode* _camNode = nullptr;
	Ogre::Viewport * _viewPort = nullptr;

	
};


#endif // 
