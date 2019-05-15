#ifndef H_SCENELOADER_H
#define H_SCENELOADER_H
///<summary>
/// SINGLETON THAT LOADS THE SCENE SPECIFIED IN THE JSON THAT FILEREADER READS
/// IT CREATES THE COMPONENTS, ENITITIES, EVENTS
/// CALLED FROM THE SCENE
///</summary>

#include "Factory.h"
#include "Component.h"

struct typeOfEntity
{
	std::string type; //id of entity
	std::map<std::string, std::map<std::string, Arguments>> components; //components and arguments
	std::map<std::string, std::vector<std::string>> events; //events of each component
};

class SceneLoader
{
public:
	~SceneLoader();
	

	///<summary>
	/// creates the instance or returns one already created. necessary for the singleton pattern
	///</summary>
	static SceneLoader* GetInstance();

	///<summary>
	/// created the enitities, components and events from the json file that receives
	///</summary>
	///<param name="json">the file that has been read. contains all the info of objects to be created</param>
	///<param name="compFactory">contains a map of the components abailable with their constructors. necessary for the factory pattern</param>
	std::map<std::string, typeOfEntity> LoadFromJson(nlohmann::json json, Factory<Component>compFactory);

	

private:
	///<summary>
	/// keep the constructor private for the singleton pattern
	///</summary>
	SceneLoader();

	///<summary>
	/// _instance of the singleton
	///</summary>
	static SceneLoader* _instance;
};
#endif