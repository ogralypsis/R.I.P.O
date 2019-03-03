#include "MyOgre.h"
#include <iostream>


MyOgre::MyOgre()
{
	
}


MyOgre::~MyOgre()
{
}

bool MyOgre::InitOgre()
{

	CreateRoot();

	return true;
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


	if (OneTimeConfig())
		SetUp();

}

bool MyOgre::OneTimeConfig()
{

	if (!_root->restoreConfig())
	{
		return _root->showConfigDialog(NULL);
	}
	else return true;
}

void MyOgre::SetUp()
{

	// initialise root
	_root->initialise(false, "R.I.P.O");

	// create main window
	_window = _root->createRenderWindow("R.I.P.O", 800, 640, false);

	// get the resource manager
	Ogre::ResourceGroupManager &_resGroupMgr = Ogre::ResourceGroupManager::getSingleton();
	// tell it to look at this location
	_resGroupMgr.addResourceLocation("Resources", "FileSystem", "Essential");

	try {
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
	}
	catch (Ogre::Exception e)
	{
#ifdef _DEBUG

		std::cout << e.what() << std::endl;
		//return false;
#endif // _DEBUG
	}


	Ogre::ConfigFile cf;

	try {
		cf.load(_resourcesConfigLoc);
	}
	catch (Ogre::Exception e) {
		std::cout << "\n" << e.getFile();
	}


	//name: Path to resources in disk,
	//loctype: defines what kind of location the element is (e.g. Filesystem, zip..)
	//Ogre::String name, locType;

	//We now iterate through each section in the resources.cfg.
	//Sections are signaled as [NAME]		

	//name: Path to resources in disk,
	//locType: defines what kind of location the element is (e.g. Filesystem, zip..),
	//sec: defines to what section the file belongs
	Ogre::String sec, locType, name;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			locType = i->first;
			name = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			_resGroupMgr.addResourceLocation(name, locType, sec);
		}
	}

	//Resources Init

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Now we init every resource previously added
	try {

		_resGroupMgr.initialiseAllResourceGroups(); // De momento "Essential" y defecto creado por ogre al no especificar.
	}
	catch (Ogre::Exception e) {
#ifdef DEBUG
		std::cout << e.what() << std::endl;

#endif // DEBUG
	}


}


