#ifndef _MYOGRE_H
#define _MYOGRE_H


#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreConfigDialog.h>
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreCamera.h>


class MyOgre
{
public:
	MyOgre();
	~MyOgre();

	/// <summary>
	/// Initialize Ogre with plugins and resources configuration 
	/// </summary>
	bool InitOgre();

	/// <summary>
	/// Release all pointers used, resources and ogre manually
	/// </summary>
	void Shutdown();

	/// <summary>
	/// Returns the singleton for the OGRE API
	/// </summary>
	static MyOgre& GetInstance();

	/// <summary>
	/// Release the OGRE API instance created previously
	/// </summary>
	static void ResetInstance();

	/// <summary>
	/// Returns the main camera of the scenes with the viewport
	/// </summary>
	Ogre::Camera* CreateCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr);

	/// <summary>
    /// Returns the main light of the scenes
	/// </summary>
	void CreateLight(Ogre::SceneManager * sceneMgr);

private:

	/// <summary>
	/// Create ogre root object with the given plugins path
	/// </summary>
	void CreateRoot();

	/// <summary>
	/// Configure ogre application with saved video/sound/etc settings; if there isn't saved a configuration already, the first available render system with the default options will be selected
	/// </summary>
	bool OneTimeConfig();

	/// <summary>
	/// Initialize ogre root object and create the render window. Also call LocateResources() and LoadResources()
	/// </summary>
	bool SetUp();

	/// <summary>
	/// Locate in the reources group manager all the resources within the resources.cfg and group them in resources group
	/// </summary>
	bool LocateResources();

	/// <summary>
	/// Initialize all resource previously added to the reources group manager
	/// </summary>
	bool LoadResources();


	static MyOgre * _instance;


	Ogre::Root * _root;
	Ogre::RenderWindow * _window;
	Ogre::SceneManager * _sceneMgr;
	Ogre::Camera* _mainCamera;
	Ogre::Viewport * _viewPort;
	Ogre::Light* _light;

	
	// Path for resources.cfg
	Ogre::String _resourcesConfigLoc;
	// Path for plugins.cfg
	Ogre::String _pluginsConfigLoc;
};
#endif
