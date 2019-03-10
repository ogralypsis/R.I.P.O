#ifndef GAME_H
#define GAME_H
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


	static Game * _instance;

	
};
#endif
