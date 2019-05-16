#include "CameraManager.h"
#include <iostream>
#include "Euler.h"


CameraManager* CameraManager::_instance = nullptr;

void CameraManager::AttachPlayer(std::string mesh, Ogre::SceneNode * playerNode)
{
	_player = playerNode;
	_gunMesh = mesh;
}

Ogre::Vector3 CameraManager::GetGunPos()
{
	return _gunPos;
}


CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
	if (_player != nullptr) 
	{
		_player = nullptr;
		delete _player;
	}
	if (_camNode != nullptr)
	{
		_camNode = nullptr;
		delete _camNode;
	}
	if (_camera != nullptr)
	{
		_camera = nullptr;
		delete _camera;
	}
	if (_viewPort != nullptr)
	{
		_viewPort = nullptr;
		delete _viewPort;
	}
}

void CameraManager::CreateCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr)
{
	//if there is no player
	if (_player == nullptr)
	{
		_camNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
		_camNode->setPosition(Ogre::Vector3(-80, 10, 5));
	}
	else //if there is a player, create camNode as the player's child
	{
		_camNode = _player->createChildSceneNode();
		//rotates camNode to face same direction as parent node
		_camNode->yaw(Ogre::Degree(-180), Ogre::Node::TS_LOCAL);
		Ogre::Vector3 pos (_camNode->getPosition().x, _camNode->getPosition().y+5, _camNode->getPosition().z - 20);
		_camNode->setPosition(pos);

		//Create the gun entity to attach its node to de camNode
		Ogre::Entity* _gunEntity = sceneMgr->createEntity(_gunMesh);
		Ogre::SceneNode* _gunNode = _camNode->createChildSceneNode();
		_gunNode->attachObject(_gunEntity);

		_gunPos = Ogre::Vector3(_gunNode->getPosition().x + 6, _gunNode->getPosition().y, _gunNode->getPosition().z - 20);
		_gunNode->setPosition(_gunPos);
		_gunNode->setScale(Ogre::Vector3 (3, 3, 3));
		_gunNode->roll(Ogre::Degree(90), Ogre::Node::TS_LOCAL);
		_gunNode->yaw(Ogre::Degree(80), Ogre::Node::TS_LOCAL);
		_gunNode->roll(Ogre::Degree(25), Ogre::Node::TS_LOCAL);
		

	}

	//add a camera
	_camera = sceneMgr->createCamera("FPScam");

	_camera->lookAt(Ogre::Vector3(0, 0, 0));
	_camera->setNearClipDistance(5);
	_camera->setFarClipDistance(10000);

	_camNode->attachObject(_camera);

	// add viewport
	_viewPort = window->addViewport(_camera);
	_viewPort->setAutoUpdated(true);
}



Ogre::Quaternion CameraManager::FPSrotation(float time, Ogre::Real mouseX, Ogre::Real mouseY)
{
	//Y axis rotation on player
	_rotY = -mouseX;
	_player->yaw(Ogre::Degree(_rotY) * _rotSpeed * time);

	//X axis rotation on player
	_rotX = -mouseY;
	Ogre::Real nextPitch = -_camNode->getOrientation().getPitch().valueDegrees() + _rotX;

	//check if max camera height has been reached
	if (nextPitch > -_maxPitch && nextPitch < _maxPitch)
		_camNode->pitch(Ogre::Degree(_rotX) * _rotSpeed * time);

	Ogre::Matrix3 m = Ogre::Matrix3();
	_player->getOrientation().ToRotationMatrix(m);


	Ogre::Radian y = Ogre::Radian();
	Ogre::Radian x = Ogre::Radian();
	Ogre::Radian z = Ogre::Radian();

	m.ToEulerAnglesYXZ(y, x, z);

	Ogre::Euler e(y, x, z);

	Ogre::Quaternion q = e;
	
	return q;
	
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



