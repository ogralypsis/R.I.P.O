#ifndef _MYOGRE_H
#define _MYOGRE_H


#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreConfigDialog.h>
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>
#include <OgreFileSystemLayer.h>


class MyOgre
{
public:
	MyOgre();
	~MyOgre();


	// Initialize Ogre with plugins and resources configuration 
	bool InitOgre();

private:

	void CreateRoot();
	bool OneTimeConfig();
	void SetUp();


	Ogre::Root * _root;
	Ogre::RenderWindow * _window;
	//Ogre::ResourceGroupManager &_resGroupMgr;

	Ogre::String _resourcesConfigLoc;
	Ogre::String _pluginsConfigLoc;
};
#endif
