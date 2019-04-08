#include "CameraManager.h"

CameraManager* CameraManager::_instance = nullptr;


CameraManager::~CameraManager()
{
	if (_mainCamera)
	{
		delete _mainCamera;
		_mainCamera = nullptr;
	}
	if (_camNode)
	{
		delete _camNode;
		_camNode = nullptr;
	}
}

void CameraManager::CreateMainCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr)
{
	// add a camera
	Ogre::Camera *camera = sceneMgr->createCamera("MainCam");
	_camNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

	camera->setPosition(Ogre::Vector3(0, 160, 160));
	camera->lookAt(Ogre::Vector3(0, 0, 0));
	camera->setNearClipDistance(5);
	camera->setFarClipDistance(10000);

	_camNode->attachObject(camera);
	_camNode->setPosition(0, 0, 140);

	// add viewport
	_viewPort = window->addViewport(camera);
}

CameraManager & CameraManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CameraManager();
	return *CameraManager::_instance;

}

void CameraManager::ResetInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}
