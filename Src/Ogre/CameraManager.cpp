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
	_player->setPosition(Ogre::Vector3(30, 10, 200));

	//add a camera
	_camera = sceneMgr->createCamera("FPScam");
	_camNode = _player->createChildSceneNode();

	_camera->lookAt(Ogre::Vector3(0, 0, 0));
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


void CameraManager::CreateMainCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr)
{
	 //add a camera
	_camera = sceneMgr->createCamera("MainCam");
	_camNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

	_camera->setPosition(Ogre::Vector3(0, 160, 160));
	_camera->lookAt(Ogre::Vector3(0, 0, 0));
	_camera->setNearClipDistance(5);
	_camera->setFarClipDistance(10000);
	
	//camera yaw node
	//_camYawNode = _camNode->createChildSceneNode();

	//camera pitch node
	//_camPitchNode = _camYawNode->createChildSceneNode();


	_camNode->attachObject(_camera);
	_camNode->setPosition(0, 0, 0);
	_camNode->setFixedYawAxis(true);

	// add viewport
	_viewPort = window->addViewport(_camera);
	_viewPort->setAutoUpdated(true);
}


void CameraManager::CameraMovement(Ogre::Real time)
{

	float rotX = 0;
	float rotY = 0;
	if (newMouseCoords.mouseX < oldMouseCoords.mouseX)
	{
		_direction.x = -1;
		rotX = -newMouseCoords.mouseX;
		//rotX = Ogre::Radian(Ogre::Degree(-90));
	}
	else if (newMouseCoords.mouseX > oldMouseCoords.mouseX)
	{
		_direction.x = 1;
		rotX = newMouseCoords.mouseX;
		//rotX = Ogre::Radian(Ogre::Degree(90));
	}
	else
	{
		_direction.x = 0;
	}
	//Ogre::Vector3 translate = { _direction.x,0,0 };
	//

	//Ogre::Radian rotY = Ogre::Radian(0);

	if (newMouseCoords.mouseY < oldMouseCoords.mouseY)
	{
		_direction.y = -1;
		rotY = -newMouseCoords.mouseY;
	}
	else if (newMouseCoords.mouseY > oldMouseCoords.mouseY)
	{
		_direction.y = 1;
		rotY = newMouseCoords.mouseY;
	}
	else
	{
		_direction.y = 0;
	}

	float currentCameraPitch = _camNode->getOrientation().getPitch().valueDegrees();
	float nextcameraPitch = currentCameraPitch + (rotY * 0.15f);
	
	if (nextcameraPitch < 10.0f && nextcameraPitch > -10.0f)
		_camNode->pitch(Ogre::Degree(rotY*0.15f) * time);

	_camNode->yaw(Ogre::Degree(rotX*0.15f) * time, Ogre::Node::TS_PARENT);
	//Ogre::Vector3 movement(0, 0, 0);
	//Ogre::Vector3 direction = _camNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	//direction.normalise();

	//Ogre::Radian rotX = Ogre::Radian(0);
	//
	

	//

	//_camNode->yaw(Ogre::Radian(rotX) * time, Ogre::SceneNode::TS_WORLD);

	////_camNode->translate(_direction * time, Ogre::SceneNode::TS_WORLD);

	////_camNode->translate(_camNode->getOrientation(), Ogre::SceneNode::TS_LOCAL);

	////_camNode->pitch(Ogre::Radian(rotY)* time);
	////_camNode->translate(_camNode->getOrientation() * translate * time * _move, Ogre::SceneNode::TS_LOCAL);
	////_camera->moveRelative(translate * time * _move);
	//
	////_camPitchNode->pitch(rotY * time, Ogre::Node::TS_LOCAL);
	////
	////Ogre::Vector3 _translateVector = { _direction.x,_direction.y,0 };
	////_camNode->translate(_camYawNode->getOrientation() *
	////	_camPitchNode->getOrientation() * _translateVector, Ogre::SceneNode::TS_LOCAL);

	////
	//oldMouseCoords = newMouseCoords;
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

