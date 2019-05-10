#ifndef BASE_SCENE_H
#define BASE_SCENE_H
///<summary>
/// BASE CLASS FOR THE SCENES
///</summary>

#include <EntityManager.h>
#include <EventManager.h>
#include <FileReader.h>
#include <SceneLoader.h>

class BaseScene
{
public:
	///<summary>
	/// Add a component to the entity
	///</summary>
	///<param name="id"> scene identifier </param>
	///<param name="compFactory"> list of factories of components of the game. </param>
	BaseScene(std::string id, Factory<Component> compFactory);

	~BaseScene();

	///<summary>
	/// Virtual update for every component
	///</summary>
	///<param name="t">  time since last update </param>
	virtual void Update(float t) = 0;

	///<summary>
	/// Returns the identifier of the scene
	///</summary>
	inline std::string GetId() { return _id; };

private:
	///<summary>
	/// Add the listeners to the especific events of the game
	///</summary>
	virtual void AddSceneObservers() = 0;

	///<summary>
	/// Identifier for the scene created. The map (json) will have the same name
	///</summary>
	std::string _id;
};
#endif
