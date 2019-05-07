#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include <Factory.h>
#include <Component.h>

// singletons
#include <EntityManager.h>
#include <EventManager.h>
#include <FileReader.h>
#include <SceneLoader.h>

class BaseScene
{
public:
	BaseScene(std::string ID, Factory<Component> compFactory);
	~BaseScene();

	virtual void Update(float t) = 0;
	inline std::string GetId() { return _id; };

private:

	virtual void AddSceneObservers() = 0;

	// Identifier for the scene created
	std::string _id;
};

#endif // !BASE_SCENE_H

