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
	float playerX = -15.f;
	std::vector<Entity*> m_entities;
	Camera* m_mainCamera = nullptr;
	Camera* differentCamera = nullptr;
	//Game Sounds
	std::vector<std::string> soundList;
	std::vector<soundType> soundTypes;
	std::vector<std::string> soundsToUse;
	int cameraType = 0;
	bool thirdPerson = true;
	bool isGrounded = false;
	bool soundPlaying = true;
	bool ballAttached = false;
	bool modifyControls = false;

	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void GameInit();
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void AttachBallPlayer1();
	

public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();

	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }

	inline Camera* GetCamera() { return m_mainCamera; }
	//inline CameraType* GetCameraType() { return cameraView; }
	void SetCamera(Camera* camera);
	void ChangeCamera(Camera* camera);
	//void SetCameraType(CameraType* cameraType);
};
