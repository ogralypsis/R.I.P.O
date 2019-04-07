#ifndef SCENE_H
#define SCENE_H

#include "../Engine/EntityManager.h"
#include "../Engine/FileReader.h"
#include "../Engine/factory.h"

class Scene
{
private: 
	//EntityManager _instanceEM;
	//FileReader* _instanceFR;
	std::string _sceneID;
	Factory<Component> _compFactory;
	

public:
	Scene(std::string ID, Factory<Component> compFactory);
	~Scene();

	void CreateSceneEntities(nlohmann::json scene);
	void Update();

	void AddSceneObservers();

		/*// Añadir en el json un vestor de strings eventos a la altura del vector de componentes que ya existe
		// para aqui leer ese vector de eventos y añadir el componente correspondiente como observador de es evento.
		if (entities[i].tipo == Enemy) {

			// Si la entidad tiene el componente tipo en map<string tipo, Component>componentes añadirlo como observador al evento que sea
			EventaManager.addObeserver(evento.updateTransform,)
		}*/
		


};
#endif
