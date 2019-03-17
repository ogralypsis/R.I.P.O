#include "MyOgre.h"
#include <iostream>

// Static variable for the singleton
MyOgre * MyOgre::_instance = nullptr;

MyOgre::MyOgre()
{
	_root = nullptr;
	_window = nullptr;
	_sceneMgr = nullptr;
	_mainCamera = nullptr;
	_light = nullptr;
	_viewPort = nullptr;
	_resourcesConfigLoc = "";
	_pluginsConfigLoc = "";
}


MyOgre::~MyOgre()
{
}

bool MyOgre::InitOgre()
{

	CreateRoot();
	if (OneTimeConfig())
		return SetUp();
	else return false;
	
}

void MyOgre::CreateRoot()
{

#ifdef _DEBUG
	_resourcesConfigLoc = "OgreD/resources_d.cfg";
	_pluginsConfigLoc = "OgreD/plugins_d.cfg";
#else
	_resourcesConfigLoc = "Ogre/resources.cfg";
	_pluginsConfigLoc = "Ogre/plugins.cfg";
#endif


	_root = OGRE_NEW Ogre::Root(_pluginsConfigLoc);
	
}

bool MyOgre::OneTimeConfig()
{

	if (!_root->restoreConfig())
	{
		 return _root->showConfigDialog(NULL);
	}
	else return true;
}

bool MyOgre::SetUp()
{

	// initialise root
	_root->initialise(false, "R.I.P.O");

	// create main window
	_window = _root->createRenderWindow("R.I.P.O", 800, 640, false);

	// create the scene	
	_sceneMgr = _root->createSceneManager();

	//_mainCamera = CreateCamera(_window, _sceneMgr);
	//CreateLight(_sceneMgr);

	

	return (LocateResources() && LoadResources());
		
}

void MyOgre::Shutdown()
{
	// Stores of the current configuration so it may be restored later in
	if (_root != nullptr)
	{
		_root->saveConfig();
	}

	// Delete ogre render window object
	if (_window != nullptr)
	{
		_root->destroyRenderTarget(_window);
		_window = nullptr;
	}

	Ogre::ResourceGroupManager::getSingleton().shutdownAll();

	if (_root != nullptr)
	{
		// This is normally done by Ogre automatically so don't think you have to call this yourself. 
		// However this is here for convenience, especially for dealing with unexpected errors or for systems which need to shut down Ogre on demand.
		_root->shutdown();

		// Delete root object, it has been create with "OGRE_NEW" so it must be deleted with "OGRE_DELETE"
		OGRE_DELETE _root;
		_root = nullptr;
	}
}

MyOgre & MyOgre::GetInstance()
{
	// If there wasn't created an instance for MyOgre create a new one
	if (MyOgre::_instance == nullptr)
		MyOgre::_instance = new MyOgre();

	return *MyOgre::_instance;
}

void MyOgre::ResetInstance()
{
	if (_instance != nullptr) {
		delete MyOgre::_instance;
		MyOgre::_instance = nullptr;
	}	
}

Ogre::Camera* MyOgre::CreateCamera(Ogre::RenderWindow * window, Ogre::SceneManager * sceneMgr) {

	// add a camera
	Ogre::Camera *camera = sceneMgr->createCamera("MainCam");

	camera->setPosition(Ogre::Vector3(0, 160, 160));
	camera->lookAt(Ogre::Vector3(0, 0, 0));
	camera->setNearClipDistance(5);
	camera->setFarClipDistance(10000);

	// add viewport
	_viewPort = window->addViewport(camera);

	return camera;
}

void MyOgre::CreateLight(Ogre::SceneManager * sceneMgr) {

	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	sceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

	_light = sceneMgr->createLight("MainLight");
	_light->setPosition(Ogre::Vector3(20, 80, 50));
	_light->setCastShadows(true);
}

bool MyOgre::LocateResources()
{
	// Tell the resource group manager to look at this location
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets", "FileSystem", "Essential");
	try {
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
	}
	catch (Ogre::Exception e)
	{
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		return false;
#endif // _DEBUG
	}

	Ogre::ConfigFile cf;

	try {
		cf.load(_resourcesConfigLoc);
	}
	catch (Ogre::Exception e) {
#ifdef _DEBUG
		std::cout << "\n" << e.getFile();
		return false;
#endif //_DEBUG	
	}


	// We now iterate through each section in the resources.cfg.
	// Sections are signaled as [NAME]		

	// sec: defines to what section the file belongs,
	// locType: defines what kind of location the element is (e.g. Filesystem, zip..),
	// name: path to resources in disk.
	Ogre::String sec, locType, name;

	// Go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// Go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			locType = i->first;
			name = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType, sec);
		}
	}

	return true;
}

Ogre::RenderWindow* MyOgre::GetWindow()
{
	return _window;
}

bool MyOgre::LoadResources()
{

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Now we init every resource previously added
	try {
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); // De momento "Essential" y defecto creado por ogre al no especificar.
	}
	catch (Ogre::Exception e) {
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		return false;
#endif // _DEBUG
	}

	return true;
}



