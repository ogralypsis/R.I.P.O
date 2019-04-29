#ifndef GAME_H
#define GAME_H

#include <Factory.h>
#include <Component.h>

#include "Scene.h"

#include <stack>

class Game
{
public:
	Game();
	~Game();

public:

	/// <summary>
	/// Initialize all libraries
	/// </summary>
	bool Init();

	/// <summary>
	/// Shutdown all libraries previously initialized and release objects allocated
	/// </summary>
	void Release();

	/// <summary>
	/// Main loop of the game where Input, Update and Render are called
	/// </summary>
	void Loop();

	/// <summary>
	/// Returns the singleton for the Game
	/// </summary>
	static Game& GetInstance();

	/// <summary>
	/// Release the Game instance created previously
	/// </summary>
	static void ResetInstance();

	/// <summary>
	/// Change scene
	/// </summary>
	void ChangeScene(std::string name);

	void QueueScene(std::string scene);

	void ExitGame();

private:

	/// <summary>
	/// Read and process the input taken
	/// </summary>
	void HandleInput();



	/// <summary>
	/// Update the game 
	/// </summary>
	void Update();

	/// <summary>
	/// Render one frame
	/// </summary>
	void Render();

	/// <summary>
	/// Register all components in the ComponentFactory
	/// </summary>
	void RegisterComponents();

	/// <summary>
	/// Handles window messages
	/// </summary>
	void MessagePump();


	Factory<Component> _compFactory;

	static Game * _instance;

	// game state's stack
	std::stack<Scene*> _states;
	
	// Boolean to determine the end of the game (exit the main loop)
	bool _exit;

	// World step time simulation (60 frames per second).
	const float _FPS_CAP = 1.0f / 60.0f;	

	// Game loop variables
	time_t _currentTime;
	time_t _newTime;
	float _frameTime;
	float _accumulator;
	float _inputTime;

	bool _change;
	std::string _nextScene;
	
};
#endif
