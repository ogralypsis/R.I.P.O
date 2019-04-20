#include "CameraManager.h"
#include <iostream>
CameraManager* CameraManager::_instance = nullptr;

CameraManager::CameraManager()
{
	oldMouseCoords = InputManager::GetInstance().GetMouseCoords();
	_rotate = 0.13;
	_move = 250;
	_direction = Ogre::Vector3::ZERO;
}

CameraManager::~CameraManager()
{
	if (_mainCamera )
	{
		delete _mainCamera;
		_mainCamera = nullptr;
	}
	if (_camNode != nullptr)
	{
		delete _camNode;
		_camNode = nullptr;
	}
}

void CameraManager::CreateFPSCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr)
{
	//TESTING creates a node for player
	_player = sceneMgr->getRootSceneNode()->createChildSceneNode();
	_player->setPosition(Ogre::Vector3(25, 60, 185));

	//add a camera
	_camera = sceneMgr->createCamera("FPScam");
	_camNode = _player->createChildSceneNode();

	_camera->lookAt(Ogre::Vector3(0, -0.001, 0));
	_camera->setNearClipDistance(5);
	_camera->setFarClipDistance(10000);

	_camNode->attachObject(_camera);

	// add viewport
	_viewPort = window->addViewport(_camera);
	_viewPort->setAutoUpdated(true);
}

void CameraManager::FPSrotation(Ogre::Real time)
{

	//if(oldMouseCoords.mouseX < newMouseCoords.mouseX)
}

bool CameraManager::frameStarted(const Ogre::FrameEvent & e)
{
	newMouseCoords = InputManager::GetInstance().GetMouseCoords();
	
	//CameraMovement(e.timeSinceLastFrame);
	return true;
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

