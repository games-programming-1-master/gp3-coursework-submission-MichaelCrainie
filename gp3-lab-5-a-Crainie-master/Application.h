#pragma once
#include "Entity.h"
#include <string>




class Camera;

#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()

enum AppState
{
	INITILISING, RUNNING, QUITTING
};

class Application
{
private:
	//private variables
	static Application* m_application;
	SDL_Window *m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	AppState m_appState = AppState::INITILISING;
	float m_worldDeltaTime = 0.f;
	std::vector<Entity*> m_entities;
	Camera* m_mainCamera = nullptr;
	Camera* differentCamera = nullptr;
	//Game Sounds
	std::vector<std::string> soundList;
	std::vector<soundType> soundTypes;
	std::vector<std::string> soundsToUse;
	int cameraType = 0;
	bool firstPerson = false;
	bool isGrounded = false;
	bool isGroundedPlayer2 = false;
	bool soundPlaying = true;
	bool ballAttached = false;
	bool modifyControls = true;
	int player1FreezeTimer;
	int player2FreezeTimer;
	int restartGameDelayTimer = 300;
	bool player1Frozen = false;
	bool player2Frozen = false;
	int snowPowerUpTimer = 400;
	int randomNumber;
	int redRandomNumber;
	int blueRandomNumber;
	int blueGoals;
	int redGoals;

	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void GameInit();
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void UpdateRedScore();
	void UpdateBlueScore();
	void RestartGame();

	

public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();
	//void output(int x, int y, float r, float g, float b, const char* string); //declartion for output function that takes in 2 ints, 3 floats and a const char pointer as arguments. Was used to attempt ui text but issues with Glue prevented it working as intended
	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }
	//void drawBitmapText(const char* string, float x, float y, float z);  //declaration for drawBitMapText function that takes in a const char pointer and 3 floats as arguments. Was used to attempt ui text but issues with Glue prevented it working as intended
	inline Camera* GetCamera() { return m_mainCamera; }
	
	//inline CameraType* GetCameraType() { return cameraView; }
	void SetCamera(Camera* camera);
	void ChangeCamera(Camera* camera);
	//void SetCameraType(CameraType* cameraType);
};

