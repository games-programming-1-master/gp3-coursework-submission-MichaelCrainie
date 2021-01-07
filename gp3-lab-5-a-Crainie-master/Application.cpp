#include "pch.h"
#include "Application.h"
#include "Common.h"
#include "MeshRenderer.h"
#include "Quad.h"
#include "CameraComp.h"
#include "Input.h"
#include "Resources.h"
#include "Physics.h"
#include "BoxShape.h"
#include "SphereShape.h"
#include "RigidBody.h"
#include "Camera.h"
#include "cSound.h"
#include "cSoundMgr.h"
#include "SDL2/SDL2-2.0.4/include/SDL.h"
#include "SDL2/SDL2_ttf-2.0.14/include/SDL_ttf.h"
#include <SDL_ttf.h>














Application *Application::m_application = nullptr; 
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance(); //creates an instance of the sound manager 
Entity* groundPlane = new Entity();
Entity* player1 = new Entity(glm::vec3(0.f, 5.f, 60.f), glm::quat({ 0, 0, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* thirdPersonCamera = new Entity(glm::vec3(0.f, 5.f, 70.f), glm::quat({ 0, 0, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* ball = new Entity(glm::vec3(0.f, 0.f, -20.f), glm::quat({ 0, 0, 0 }), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.f, 0.f, 5.f));
Entity* goals1 = new Entity(glm::vec3(0.f, -10.f, -100.f), glm::quat({ 0, 0, 0 }), glm::vec3(5.1f, 5.1f, 5.1f), glm::vec3(0.f, 0.f, 5.f));
Entity* goals2 = new Entity(glm::vec3(0.f, -10.f, 70.f), glm::quat({ 0, 160.3f, 0 }), glm::vec3(5.1f, 5.1f, 5.1f), glm::vec3(0.f, 0.f, 5.f));
Entity* wall1 = new Entity(glm::vec3(0.f, -10.f, 100.f), glm::quat({ 0, 0, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* wall2 = new Entity(glm::vec3(0.f, -10.f, -140.f), glm::quat({ 0, 0, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* wall3 = new Entity(glm::vec3(80.f, -10.f, -120.f), glm::quat({ 0, 20.4f, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* wall4 = new Entity(glm::vec3(-100.f, -10.f, -120.f), glm::quat({ 0, 20.4f, 0 }), glm::vec3(80.1f, 15.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* player2 = new Entity(glm::vec3(0.f, 5.f, -60.f), glm::quat({ 0, 0, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* snowFlakePowerUp = new Entity(glm::vec3(-400.f, -8.f, 30.f), glm::quat({ 0, 0, 0 }), glm::vec3(15.f, 15.f, 15.f), glm::vec3(0.f, 0.f, 5.f));
Entity* blueTeamName = new Entity(glm::vec3(75.f, 55.f, 20.f), glm::quat({ 1, 0, -1, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* redTeamPoints = new Entity(glm::vec3(75.f, 55.f, -20.f), glm::quat({ 1, 0, -1, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* redTeamName = new Entity(glm::vec3(75.f, 55.f, -80.f), glm::quat({ 1, 0, -1, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* blueTeamPoints = new Entity(glm::vec3(75.f, 55.f, -10.f), glm::quat({ 1, 0, -1, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* winningTeam = new Entity(glm::vec3(75.f, 35.f, -40.f), glm::quat({ 1, 0, -1, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));     //Lines 35 - 51: Create entities(objects) to be used in the game also setting their positions, rotations, scales and XYZ trans
glm::vec3 player1Start = glm::vec3(0.f, 5.f, 60.f); //starting location for the player
glm::vec3 player2Start = glm::vec3(0.f, 5.f, -80.f); //starting location for player2 stored as a vec3
glm::vec3 ballStart = glm::vec3(0, 0, -20.f);  //starting location for the ball stored as a vec3
SDL_Event event;
CameraComp* firstPersonCamera = new CameraComp(); //first camera that is attached to the player object later on. First person perspective
CameraComp* sideOnCamera = new CameraComp(); //camera that is attached to the ground plane later on. Side on perspective to view both players 
//glm::vec3 ballX; //Un used vec3 was used for testing dodgeball style game
const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); //creates const 8-bit unsigned int pointer and sets the keybaord state to null by default

Application::Application()
{
}



void Application::Init()
{
	
	//TTF_Init(); //was used to initialize  TTF 
	SDL_Init(SDL_INIT_VIDEO);
	//if (TTF_Init() < 0)
	//{
		//printf("NOOOOOOOOO"); //if TTF fails to initialize print this string
	//}
	
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_DEBUG(SDL_GetError());
		exit(-1);
	}

	//setting openGL version to 4.2 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//setting openGL context to core, not compatibility
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//creating window
	m_window = SDL_CreateWindow("Locket Reague", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight,
		SDL_WINDOW_OPENGL);

	//m_renderTarget = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/*TTF_Font *font = TTF_OpenFont("COMICATE.ttf", 20);
	SDL_Color color = { 144, 77, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Red Team 0 - 0 Blue Team", color);
	SDL_Texture *text = SDL_CreateTextureFromSurface(m_renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	SDL_RenderCopy(m_renderTarget, text, NULL, &textRect);
	SDL_RenderPresent(m_renderTarget);*/                            //Lines 102 - 113: Creates an SDL renderer, sets the font to be used, color to be used then creates a surface and texture from the text that is to be displayed. 
	                                                                                 //This texture is then to be applied to a rectangle which will be displayed to the screen via the renderer created     
	                                                                                //This code is commented out as it only displayed the score for a split second and would disappear and also caused an issue creating a release version. Comment back in to see effect 
	SDL_CaptureMouse(SDL_TRUE); //enables capture of mouse

	OpenGlInit();
	GameInit();
	//gitHub test
	
}

/*void Application::drawBitmapText(const char* string, float x, float y, float z)
{
	const char* c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != NULL; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void Application::output(int x, int y, float r, float g, float b, const char* string)
{
	
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}  
}*/                                                                                   //Lines 124 - 145: Both failed attempts to display text using GLUT. Functions take in arguments about where to display on screen then filter through each char of string to display all on the screen

btVector3 glmToBullet(const glm::vec3& v)
{
	return btVector3(v.x, v.y, v.z); //handy conversion that allows a glm::vec3 to be converted into a btVector3 and then used in many of the bullet libraries functions.
}
/*void drawText(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double(16);
	glLoadIdentity();
	glOrtho(0, 800, 0, -600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, int(text[i]));
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void DrawScreen(SDL_Surface* screen, int h)
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

	gluLookAt(0, 0, -10, 0, 0, 3, 0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	std::string text;
	text = "please work";
	drawText(text.data(), text.size(), 0, 0);

	//

}*/ //Lines 151 - 187: Another failed attempt at rendering text to the screen

void Application::OpenGlInit()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);
	CHECK_GL_ERROR();

	SDL_GL_SetSwapInterval(1);

	//initialsing glew (do this after establishing context!)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}

	//Smooth shading
	GL_ATTEMPT(glShadeModel(GL_SMOOTH));

	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));
	//set less or equal func for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));

	//enabling blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//turn on back face culling
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	glDisable(GL_CULL_FACE);
}

void Application::GameInit()
{
	
	// Initialise the sound manager
	if (theSoundMgr->initMixer())
	{
		
		// Load game sounds
		soundList = { "theme", "click", "blueGoal", "blueGoal2", "blueGoal3", "redGoal", "redGoal2", "redGoal3", "freeze", "blueFreeze", "redFreeze", "redTeamWins", "blueTeamWins", "crowd" };
		soundTypes = { soundType::music, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx, soundType::sfx ,soundType::sfx, soundType::sfx, soundType::sfx };
		soundsToUse = { ASSET_AUDIO_PATH_Theme + "synth9.mp3", ASSET_AUDIO_PATH_SFX + "ClickOn.wav", ASSET_AUDIO_PATH_SFX + "blueTeamGoal.wav", ASSET_AUDIO_PATH_SFX + "blueTeamGoal4.wav", ASSET_AUDIO_PATH_SFX + "blueTeamGoal5.wav", ASSET_AUDIO_PATH_SFX + "redTeamGoal2.wav", ASSET_AUDIO_PATH_SFX + "redTeamGoal3.wav", ASSET_AUDIO_PATH_SFX + "redTeamGoal4.wav", ASSET_AUDIO_PATH_SFX + "freezePower.wav", ASSET_AUDIO_PATH_SFX + "blueTeamFreeze.wav", ASSET_AUDIO_PATH_SFX + "redTeamFreeze.wav", ASSET_AUDIO_PATH_SFX + "redTeamWins.wav", ASSET_AUDIO_PATH_SFX + "blueTeamWins.wav", ASSET_AUDIO_PATH_SFX + "crowdCheer2.wav" };
		for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
		{
			theSoundMgr -> add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]); //add the soundList, soundTypes and soundsToUse to sound manager enabling them to be called
		}
		// Play the theme on a constant loop
		theSoundMgr->getSnd("theme")->play(-1);
	}
	//loading all resources
	Resources::GetInstance()->AddModel("Models/cube.obj");
	Resources::GetInstance()->AddModel("Models/portal.obj");
	Resources::GetInstance()->AddModel("Models/cube2.obj");
	Resources::GetInstance()->AddModel("Models/football.obj");
	Resources::GetInstance()->AddModel("Models/wall.obj");
	Resources::GetInstance()->AddModel("Models/goals.obj");
	Resources::GetInstance()->AddModel("Models/footballBoot3.obj");
	Resources::GetInstance()->AddModel("Models/footballBoot4.obj");
	Resources::GetInstance()->AddModel("Models/emptyObject.obj");
	Resources::GetInstance()->AddModel("Models/snowflakes.obj");
	Resources::GetInstance()->AddModel("Models/icecube2.obj");
	Resources::GetInstance()->AddModel("Models/five.obj");
	Resources::GetInstance()->AddModel("Models/fiveNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/fourNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/four.obj");
	Resources::GetInstance()->AddModel("Models/one.obj");
	Resources::GetInstance()->AddModel("Models/one1.obj");
	Resources::GetInstance()->AddModel("Models/oneNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/three.obj");
	Resources::GetInstance()->AddModel("Models/threeNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/two.obj");
	Resources::GetInstance()->AddModel("Models/twoNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/zeroNoHyph.obj");
	Resources::GetInstance()->AddModel("Models/redTeamWins.obj");
	Resources::GetInstance()->AddModel("Models/blueTeamWins.obj");
	Resources::GetInstance()->AddModel("Models/blueTeam.obj");
	Resources::GetInstance()->AddModel("Models/redTeam.obj");
	Resources::GetInstance()->AddTexture("Images/Textures/Wood.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Gold.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Ice.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/IceBlue.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Silver.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/road.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/grass.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/leather.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/wall.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Sapphire.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Ruby.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/football.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/frozen.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Red.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Blue.jpg");
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/simple_VERT.glsl", 
		ASSET_PATH + "Shaders/simple_FRAG.glsl"), 
		"simple"
		
	);

	
	m_entities.push_back(groundPlane); //Adds object to m_entities vector(array) 
	groundPlane->AddComponent( 
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/cube.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/grass.jpg")) //attached mesh rendering and sets the model, shader and texture to use
	);
	MeshRenderer* m = groundPlane->GetComponent<MeshRenderer>(); //creates mesh renderer variable and sets it to the mesh renderer attached to this entity 
	groundPlane->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f)); //sets position of this entity 
	groundPlane->AddComponent<RigidBody>(); //adds rigid body to entity 
	groundPlane->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 150.f))); //adds box shape collider to the rigid body and sets the size of it to the glm::vec3 passed in
	groundPlane->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3()); //makes the rigid body static so it is not impacted by other rigid bodies 
	groundPlane->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 150.f)); //sets the scale of the entity
	groundPlane->GetComponent<RigidBody>()->Get()->setFriction(1); //sets the friction of entity's rigid body 

	
	//
	//   All other entities below have practically the exact same things applied to them with slight modifications. Any new things applied will be noted upon reaching them
	//	 
	//

	m_entities.push_back(goals1);
	goals1->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/goals.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Gold.jpg"))
	);
	MeshRenderer* p = goals1->GetComponent<MeshRenderer>();
	goals1->AddComponent<RigidBody>();
	goals1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(14.f, 5.f, 0.05f)));
	goals1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	goals1->GetComponent<RigidBody>()->Get()->setFriction(1); 
	goals1->GetComponent<RigidBody>()->Get()->setRestitution(1); //set restitution (bouncyness)

	m_entities.push_back(wall1);
	wall1->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* r = wall1->GetComponent<MeshRenderer>();
	wall1->AddComponent<RigidBody>();
	wall1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 3000.f, 1.f)));
	wall1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	wall1->GetComponent<RigidBody>()->Get()->setFriction(1);
	wall1->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(wall2);
	wall2->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* s = wall2->GetComponent<MeshRenderer>();
	wall2->AddComponent<RigidBody>();
	wall2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 3000.f, 1.f)));
	wall2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	wall2->GetComponent<RigidBody>()->Get()->setFriction(1);
	wall2->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(wall3);
	wall3->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* t = wall3->GetComponent<MeshRenderer>();
	wall3->AddComponent<RigidBody>();
	wall3->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(300.f, 3000.f, 5.f)));
	wall3->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	wall3->GetComponent<RigidBody>()->Get()->setFriction(1);
	wall3->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(wall4);
	wall4->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* u = wall4->GetComponent<MeshRenderer>();
	wall4->AddComponent<RigidBody>();
	wall4->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(300.f, 3000.f, 5.f)));
	wall4->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	wall4->GetComponent<RigidBody>()->Get()->setFriction(1);
	wall4->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(goals2);
	goals2->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/goals.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Gold.jpg"))
	);
	MeshRenderer* q = goals2->GetComponent<MeshRenderer>();
	goals2->AddComponent<RigidBody>();
	goals2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(14.f, 5.f, -0.05f)));
	goals2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	goals2->GetComponent<RigidBody>()->Get()->setFriction(1);
	goals2->GetComponent<RigidBody>()->Get()->setRestitution(1);
	
	m_entities.push_back(player1);
	player1->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/footballBoot3.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Sapphire.jpg"))
	);
	MeshRenderer* n = player1->GetComponent<MeshRenderer>();
	player1->AddComponent<RigidBody>();
	player1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.f, 1.f, 5.f)));
	player1->GetComponent<RigidBody>()->Get()->setFriction(1);
	player1->GetComponent<RigidBody>()->Get()->setSpinningFriction(1); //sets spinning friction
	player1->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0)); //stops the player spinning 
	player1->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(snowFlakePowerUp);
	snowFlakePowerUp->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/snowflakes.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/IceBlue.jpg"))
	);

	MeshRenderer* z = snowFlakePowerUp->GetComponent<MeshRenderer>();
	snowFlakePowerUp->AddComponent<RigidBody>();
	snowFlakePowerUp->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 20.f)));
	snowFlakePowerUp->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	m_entities.push_back(player2);
	player2->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/footballBoot4.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Ruby.jpg"))
	);
	MeshRenderer* v = player2->GetComponent<MeshRenderer>();
	player2->AddComponent<RigidBody>();
	player2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.f, 1.f, 5.f)));
	player2->GetComponent<RigidBody>()->Get()->setFriction(1);
	player2->GetComponent<RigidBody>()->Get()->setSpinningFriction(1);
	player2->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0));
	player2->GetComponent<RigidBody>()->Get()->setRestitution(1);
	
	
	m_entities.push_back(ball);
	ball->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/football.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/football.jpg"))
	);
	MeshRenderer* o = ball->GetComponent<MeshRenderer>();
	ball->AddComponent<RigidBody>();
	ball->GetComponent<RigidBody>()->Init(new SphereShape(1)); //adds sphere shape collider to the rigid body of the entity with a radius of 1 which is a btScalar
	ball->GetComponent<RigidBody>()->Get()->setFriction(0.1);
	ball->GetComponent<RigidBody>()->Get()->setRollingFriction(0.1); //sets the rolling friction to a low number in order to keep the ball moving even with low force being applied to it
	ball->GetComponent<RigidBody>()->Get()->setRestitution(1);
	ball->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0.f, 0, 0.f));
	
	m_entities.push_back(redTeamName);
	redTeamName->AddComponent(
	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/redTeam.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/Red.jpg")));
	MeshRenderer* zz = redTeamName->GetComponent<MeshRenderer>();
	redTeamName->AddComponent<RigidBody>();
	redTeamName->GetComponent<RigidBody>()->Init(new SphereShape(0)); 
	redTeamName->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	m_entities.push_back(blueTeamName);
	blueTeamName->AddComponent(
	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/blueTeam.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/Blue.jpg")));
	MeshRenderer* qq = redTeamName->GetComponent<MeshRenderer>();
	blueTeamName->AddComponent<RigidBody>();
	blueTeamName->GetComponent<RigidBody>()->Init(new SphereShape(0));
	blueTeamName->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	m_entities.push_back(redTeamPoints);
	redTeamPoints->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/one.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg")));
	MeshRenderer* pp = redTeamPoints->GetComponent<MeshRenderer>();
	redTeamPoints->AddComponent<RigidBody>();
	redTeamPoints->GetComponent<RigidBody>()->Init(new SphereShape(0));
	redTeamPoints->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	m_entities.push_back(blueTeamPoints);
	blueTeamPoints->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/zeroNoHyph.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg")));
	MeshRenderer* ll = blueTeamPoints->GetComponent<MeshRenderer>();
	blueTeamPoints->AddComponent<RigidBody>();
	blueTeamPoints->GetComponent<RigidBody>()->Init(new SphereShape(0));
	blueTeamPoints->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	m_entities.push_back(winningTeam);
	winningTeam->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/emptyObject.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg")));
	MeshRenderer* mm = winningTeam->GetComponent<MeshRenderer>();
	winningTeam->AddComponent<RigidBody>();
	winningTeam->GetComponent<RigidBody>()->Init(new SphereShape(0));
	winningTeam->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	


	
	
	
	
	//thirdPersonCamera->AddComponent<RigidBody>();

	for (int i = 0; i < 10; i++) //for loop for crates that are outside the field of play, lower X value of the glm::vec3 in line 529 if you wish to see how the they interact with the players and the ball once they have fallen over
	{
		Entity* a = new Entity();
		m_entities.push_back(a);
		a->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/cube.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/Wood.jpg"))
		);
		a->GetTransform()->SetPosition(glm::vec3(100, 5.f * i, -60.f));
		a->AddComponent<RigidBody>();
		a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)));
		a->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		


	}
	//Lines 539 - 622: creates mesh renderers that hold obj's/textures that are not currently in use at the start of the game
	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/portal.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/football.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/emptyObject.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/football.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/icecube2.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/five.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/Red.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/fiveNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/four.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/fourNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/one.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/oneNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/one1.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/zeroNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/three.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/threeNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/two.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/twoNoHyph.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/blueTeamWins.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));

	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/redTeamWins.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));
	
	player1->AddComponent(firstPersonCamera); //add the firstPersonCamera cameraComp to the entity of player1
	//cc->Start();
	groundPlane->AddComponent(sideOnCamera); //add the sideOnCamera cameraComp to the entity of groundPlane
	sideOnCamera->Start(); //sets the sideOnCamera to be active camera
	m_mainCamera->DifferentCameraView(); //calls the DifferentCameraView function from camera.cpp and applies it to m_mainCamera (will be explained further in camera cpp)
	

	

	



	
	SDL_SetRelativeMouseMode(SDL_TRUE); //keeps mouse movement relative to the game window
	Resources::GetInstance()->ReleaseUnusedResources();
	std::cout << "CONTROLS: PLAYER1 ARROW KEYS TO MOVE" << std::endl; //controls to debug console
	std::cout << "CONTROLS: PLAYER1 NUMPAD 0 TO JUMP IF ON GROUND" << std::endl;
	std::cout << "CONTROLS: PLAYER1 C KEY TO TOGGLE CAMERAS" << std::endl;
	std::cout << "CONTROLS: PLAYER1 TAB KEY TO TOGGLE MUSIC" << std::endl;
	std::cout << "CONTROLS: PLAYER1 MOUSE TO MOVE CAMERA IN FIRST PERSON MODE, MOVEMENT WILL BE RELATIVE TO DIRECTION" << std::endl;
	std::cout << "CONTROLS: PLAYER1 ENTER KEY TO RESET POSITION" << std::endl;
	std::cout << "CONTROLS: PLAYER2 WASD KEYS TO MOVE" << std::endl;
	std::cout << "CONTROLS: PLAYER2 SPACE BAR TO JUMP IF ON GROUND" << std::endl;
	std::cout << "CONTROLS: PLAYER2 R KEY TO RESET POSITION" << std::endl;
	std::cout << "CONTROLS: PLAYER1 BACKSPACE AND PLAYER2 Z KEY TO RESET BALL (SAME TIME)" << std::endl;
	std::cout << "GAMEPLAY: PLAYER WILL FREEZE OTHER PLAYER UPON COLLIDING WITH ICE POWERUP" << std::endl;
	std::cout << "GAMEPLAY: PLAYERS CANNOT MOVE WHILE FROZEN" << std::endl;
	std::cout << "WIN CONDITION: FIRST TO 5 GOALS!" << std::endl;
}

void Application::Loop()
{
	


	m_appState = AppState::RUNNING;
	//std::cout << playerX << std::endl;
	auto prevTicks = std::chrono::high_resolution_clock::now();
	//player1->GetComponent<RigidBody>()->UpdateParent();
	//player1->GetComponent<RigidBody>()->UpdateRigidBody();
	ball->GetComponent<RigidBody>()->UpdateParent();
	ball->GetComponent<RigidBody>()->UpdateRigidBody();
	//ballX = player1->GetTransform()->GetPosition();

	while (m_appState != AppState::QUITTING)
	{
		
		if (snowPowerUpTimer > 0) //if this integer is higher than 0 decrement it
		{
			snowPowerUpTimer--;
		}

		if (redGoals == 5 || blueGoals == 5) //if either team reaches 5 goals decrement the restartGameDelayTimer
		{
			restartGameDelayTimer--;
		}

		if (restartGameDelayTimer <= 0) //if the restartGameDelayTimer is less than or equal to 0 call the RestartGame function
		{
			RestartGame();
		}

		if (snowPowerUpTimer <= 0)   //if snowPowerUpTimer is less than or equal to 0 generate a random number between 1 and 8 then move the power up to the correspnding position. Timer will then reset to 3000
		{
			
			randomNumber = 1 + (rand() % 8);
			switch (randomNumber)
			{
			case 1:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(65.f, -8.f, 30.f));
				snowPowerUpTimer = 3000;
				break;

			case 2:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(65.f, -8.f, -30.f));
				snowPowerUpTimer = 3000;
				break;
			case 3:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(65.f, -8.f, -60.f));
				snowPowerUpTimer = 3000;
				break;
			case 4:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(65.f, -8.f, -80.f));
				snowPowerUpTimer = 3000;
				break;
			case 5:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(-65.f, -8.f, 30.f));
				snowPowerUpTimer = 3000;
				break;
			case 6:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(-65.f, -8.f, -30.f));
				snowPowerUpTimer = 3000;
				break;
			case 7:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(-65.f, -8.f, -60.f));
				snowPowerUpTimer = 3000;
				break;
			case 8:
				snowFlakePowerUp->GetTransform()->SetPosition(glm::vec3(-65.f, -8.f, -80.f));
				snowPowerUpTimer = 3000;
				break;				
				
			}
		}
		if (player1FreezeTimer > 0) //decrement player1FreezeTimer if it is more than 0
		{
			player1FreezeTimer--;
		}

		if (player2FreezeTimer > 0) //decrement player2FreezeTimer if it is more than 0
		{
			player2FreezeTimer--;
		}

		if (player2FreezeTimer <= 0 && player2Frozen == true) //if player2FreezeTimer less than or equal to 0 and player2Frozen is true set player2Frozen to false and edit the mesh and texture
		{
			player2Frozen = false;
			player2->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/footballBoot4.obj"));
			player2->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/Ruby.jpg"));
		}

		if (player1FreezeTimer <= 0 && player1Frozen == true) //if player2FreezeTimer less than or equal to 0 and player2Frozen is true set player2Frozen to false and edit the mesh and texture
		{
			player1Frozen = false;
			player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/footballBoot3.obj"));
			player1->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/Sapphire.jpg"));
		}
		snowFlakePowerUp->GetTransform()->AddRotation(glm::quat({ 0, 0.1, 0})); //sets power up to constantly rotate
		
		if (Physics::GetInstance()->Collision3D(player1->GetComponent<RigidBody>()->Get(), ball->GetComponent<RigidBody>()->Get()) == true) //if player one collides with the ball print to console 
		{
			std::cout << "HERE" << std::endl;
			//c->GetTransform()->SetPosition(glm::vec3(b->GetTransform()->GetPosition.x,);
			//ballAttached = true;
			

		}

		if (Physics::GetInstance()->Collision3D(player1->GetComponent<RigidBody>()->Get(), groundPlane->GetComponent<RigidBody>()->Get()) == true) //if player1 is colliding with ground plane set grounded to true 
		{
			//std::cout << "ground" << std::endl;
			isGrounded = true;
		}

		if (!Physics::GetInstance()->Collision3D(player1->GetComponent<RigidBody>()->Get(), groundPlane->GetComponent<RigidBody>()->Get()) == true) //if player1 is not colliding with ground plane set grounded to false
		{
			//std::cout << "ground" << std::endl;
			isGrounded = false;
		}

		if (Physics::GetInstance()->Collision3D(player2->GetComponent<RigidBody>()->Get(), groundPlane->GetComponent<RigidBody>()->Get()) == true) //if player2 is colliding with ground plane set grounded to true 
		{
			//std::cout << "ground" << std::endl;
			isGroundedPlayer2 = true;
		}

		if (!Physics::GetInstance()->Collision3D(player2->GetComponent<RigidBody>()->Get(), groundPlane->GetComponent<RigidBody>()->Get()) == true) //if player2 is not colliding with ground plane set grounded to false
		{
			//std::cout << "ground" << std::endl;
			isGroundedPlayer2 = false;
		}

		if (Physics::GetInstance()->Collision3D(player1->GetComponent<RigidBody>()->Get(), snowFlakePowerUp->GetComponent<RigidBody>()->Get()) == true) //if player1 collides with the ice power up the other player will be frozen and 2 sounds will play, the power up will also move offscreen and the timer will reset
		{
			//std::cout << "ground" << std::endl;
			player2->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/icecube2.obj"));
			player2->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));
			snowFlakePowerUp->GetTransform()->AddPosition(glm::vec3(600, 1000, 0));
			player2FreezeTimer = 200;
			snowPowerUpTimer = 2000;
			player2Frozen = true;
			theSoundMgr->getSnd("redFreeze")->play(0);
			theSoundMgr->getSnd("freeze")->play(0);
		}

		if (Physics::GetInstance()->Collision3D(player2->GetComponent<RigidBody>()->Get(), snowFlakePowerUp->GetComponent<RigidBody>()->Get()) == true) //if player2 collides with the ice power up the other player will be frozen and 2 sounds will play, the power up will also move offscreen and the timer will reset
		{
			//std::cout << "ground" << std::endl;
			player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/icecube2.obj"));
			player1->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/frozen.jpg"));
			snowFlakePowerUp->GetTransform()->AddPosition(glm::vec3(-6000, 1000, 0));
			player1FreezeTimer = 200;
			snowPowerUpTimer = 2000;
			player1Frozen = true;
			theSoundMgr->getSnd("blueFreeze")->play(0);
			theSoundMgr->getSnd("freeze")->play(0);
			
		}

		if (Physics::GetInstance()->Collision3D(ball->GetComponent<RigidBody>()->Get(), goals1->GetComponent<RigidBody>()->Get()) == true) //if the ball collides with the red team's goal add a point to the blue team, reset the player and the ball, 
			                                                                                                                               //remove all current forces from the entities, generate a random number between 1 and 3 and play the corresponding sound, 
																																		 //if it is the 5th goal of the match play the blue team wins sound
		{
			blueGoals++;
			std::cout << "Red Team " + std::to_string(redGoals) + " " +  std::to_string(blueGoals) + " Blue Team " << std::endl;
			UpdateBlueScore();
			//std::cout << "player1 Goal" << std::endl;
			player1->GetTransform()->SetPosition(player1Start);
			player2->GetTransform()->SetPosition(player2Start);
			ball->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			player1->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player1->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			ball->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			ball->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			//theSoundMgr->getSnd("blueGoal")->play(0);
			blueRandomNumber = 1 + (rand() % 3);
			if (blueGoals < 5) {
				switch (blueRandomNumber)
				{
				case 1:
					theSoundMgr->getSnd("blueGoal")->play(0);
					break;

				case 2:
					theSoundMgr->getSnd("blueGoal2")->play(0);
					break;
				case 3:
					theSoundMgr->getSnd("blueGoal3")->play(0);
					break;
				}
				theSoundMgr->getSnd("crowd")->play(0);
				if (blueGoals < 5 && redGoals < 5) {
					ball->GetTransform()->SetPosition(ballStart);
				}

			}
			else
			{
				theSoundMgr->getSnd("crowd")->play(0);
				theSoundMgr->getSnd("blueTeamWins")->play(0);
			}
		}

		if (Physics::GetInstance()->Collision3D(ball->GetComponent<RigidBody>()->Get(), goals2->GetComponent<RigidBody>()->Get()) == true) //if the ball collides with the red team's goal add a point to the blue team, reset the player and the ball, 
		{																																	//remove all current forces from the entities, generate a random number between 1 and 3 and play the corresponding sound, 
																																			//if it is the 5th goal of the match play the blue team wins sound
			redGoals++;
			std::cout << "Red Team " + std::to_string(redGoals) + " - " + std::to_string(blueGoals) + " Blue Team " << std::endl;
			UpdateRedScore();
			//std::cout << "player2 Goal" << std::endl;
			player1->GetTransform()->SetPosition(player1Start);
			player2->GetTransform()->SetPosition(player2Start);
			ball->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			player1->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player1->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			ball->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			ball->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			//theSoundMgr->getSnd("redGoal")->play(0);
			redRandomNumber = 1 + (rand() % 3);
			if (redGoals < 5) {
				switch (redRandomNumber)
				{
				case 1:
					theSoundMgr->getSnd("redGoal")->play(0);
					break;

				case 2:
					theSoundMgr->getSnd("redGoal2")->play(0);
					break;
				case 3:
					theSoundMgr->getSnd("redGoal3")->play(0);
					break;
				}
				theSoundMgr->getSnd("crowd")->play(0);
				if (blueGoals < 5 && redGoals < 5) {
					ball->GetTransform()->SetPosition(ballStart);
				}
			}

			else
			{
				theSoundMgr->getSnd("crowd")->play(0);
				theSoundMgr->getSnd("redTeamWins")->play(0);
			}
			//isGrounded = false;
		}

		//if (ballAttached == true)
		//{
			//AttachBallPlayer1();
		//}

		

		//poll SDL events
		while (SDL_PollEvent(&event))
		{
			if (firstPerson == true) //if the first person camera is active change the mesh to the empty model
			{
				player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));
			}
			player1->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.5));
			player2->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.5));
			ball->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.1f)); //damping applied to the entities which helps them slow down when no force is being applied
			switch (event.type)
			{
			case SDL_QUIT:
				m_appState = AppState::QUITTING;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				m_appState = AppState::QUITTING;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_SPACE:					
					if (isGrounded == true) 
					{ 
						//player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 10.f, 0.f)); 
					}					
					break;
				case SDLK_TAB: //used to toggle the theme sound on and off
					if (soundPlaying == true)
					{
						theSoundMgr->getSnd("theme")->StopMusic();
						soundPlaying = false;
						break;
					}

					if (soundPlaying == false)
					{
						theSoundMgr->getSnd("theme")->PlayMusic();
						soundPlaying = true;
						break;
					}
				case SDLK_c: //used to switch between cameras
					if (firstPerson == true)
					{
						player1->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
						if (player1Frozen == false) { player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/footballBoot3.obj")); }
						if (player1Frozen == true) { player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/icecube2.obj")); }
						//a->AddComponent(cc);
						sideOnCamera->Start();
						firstPerson = false;
						m_mainCamera->DifferentCameraView();
						modifyControls = true;
						break;
					}

					else
					{
						//b->AddComponent(cc);
						player1->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));
						firstPersonCamera->Start();
						firstPerson = true;
						modifyControls = false;
						break;
					}
				case SDLK_i: //isometric camera that partially works but was not finished completely
					if(cameraType == 0)
					{
						m_mainCamera->SetProjOrtho(-500, 500, -500, 500, 0.f, 1000.f);
						m_mainCamera->ModifyPositionOrtho();
						cameraType = 1;
						break;
					}

					if (cameraType == 1)
					{
						m_mainCamera->SetProjPersp(45.f, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 1000.f);
						m_mainCamera->ModifyPositionPerp();
						cameraType = 0;
						break;
					}
				case SDLK_UP:
					
					
					break;
				}
				break;
				
			//record when the user releases a key
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
				
				if (SDL_GetRelativeMouseMode() == true && modifyControls == false) //player can rotate the camera in first person mode with the mouse
				{
					m_mainCamera->GetParentTransform()->RotateEulerAxis((m_worldDeltaTime * 1)* event.motion.xrel, glm::vec3(0, 1, 0));
					m_mainCamera->GetParentTransform()->RotateEulerAxis((m_worldDeltaTime * 1)* event.motion.yrel, player1->GetTransform()->GetRight());
					//player1->GetTransform()->RotateEulerAxis((m_worldDeltaTime * 1)* event.motion.xrel, glm::vec3(0, 1, 0));
				}
				break;
			}
		}

		auto currentTicks = std::chrono::high_resolution_clock::now();
		float deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - prevTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		prevTicks = currentTicks;

		Physics::GetInstance()->Update(deltaTime);
		//update and render all entities
		Update(deltaTime);
		Render();
		if (currentKeyStates[SDL_SCANCODE_RIGHT] && player1Frozen == false) //controls for first person mode for player1, movement is relative to the direction the camera is facing in this mode. Achieved by converting the transforms right vec3 to a btVec3 and using it as a central impulse to apply to the rigid body
		{
			
			if (modifyControls == false)
			{
				//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.0f, 0.f, 0.f));
				glm::vec3 vec = player1->GetTransform()->GetRight();
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(glmToBullet(vec));
				
				
			}
			if (modifyControls == true) //controls for side on camera for player1, movement is achieved by applying central impulse to the rigid body of the entity
			{
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.0f, 0.f, 1.f));
			}
			player1->GetComponent<RigidBody>()->UpdateRigidBody(); //rigid body is updated 
			player1->GetComponent<RigidBody>()->UpdateParent(); //parent is updated
		}
		//
		//
		// controls further down operate in the same manner as previously outlined above for player 1 and 2
		//
		//
		if (currentKeyStates[SDL_SCANCODE_LEFT] && player1Frozen == false)
		{
			if (modifyControls == false)
			{
				glm::vec3 vec = player1->GetTransform()->GetRight();
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(glmToBullet(-vec));

			}
			if (modifyControls == true)
			{
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -1.f));
				

			}
			player1->GetComponent<RigidBody>()->UpdateRigidBody();
			player1->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_UP] && player1Frozen == false)
		{
			if (modifyControls == false)
			{
				glm::vec3 vec = player1->GetTransform()->GetForward();
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(glmToBullet(vec));
			}
			if (modifyControls == true)
			{
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.f, 0.f, 0.f));
			}
			//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 0.f, -4.f), btVector3(0, 0, 0));
			player1->GetComponent<RigidBody>()->UpdateRigidBody();
			player1->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_DOWN] && player1Frozen == false)
		{
			if (modifyControls == false)
			{
				glm::vec3 vec = player1->GetTransform()->GetForward();
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(glmToBullet(-vec));
			}
			if (modifyControls == true)
			{
				player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-1.5f, 0.f, 0.f));
			}
			//b->GetTransform()->AddPosition(glm::vec3(0.0f, 0.f, 1.f));		
			player1->GetComponent<RigidBody>()->UpdateRigidBody();
			player1->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_D] && player2Frozen == false )
		{

			if (modifyControls == false)
			{

				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.5f, 0.f, 0.f));
			}
			if (modifyControls == true)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.0f, 0.f, 1.5f));
			}
			player2->GetComponent<RigidBody>()->UpdateRigidBody();
			player2->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_A] && player2Frozen == false)
		{
			if (modifyControls == false)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-1.5f, 0.f, 0.f));

			}
			if (modifyControls == true)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -1.5f));

			}
			player2->GetComponent<RigidBody>()->UpdateRigidBody();
			player2->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_W] && player2Frozen == false)
		{
			if (modifyControls == false)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -1.5f));
				
			}
			if (modifyControls == true)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.5f, 0.f, 0.f));
			}
			//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 0.f, -4.f), btVector3(0, 0, 0));
			player2->GetComponent<RigidBody>()->UpdateRigidBody();
			player2->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_S] && player2Frozen == false)
		{
			if (modifyControls == false)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, 1.5f));
			}
			if (modifyControls == true)
			{
				player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-1.5f, 0.f, 0.f));
			}
			//b->GetTransform()->AddPosition(glm::vec3(0.0f, 0.f, 1.f));		
			player2->GetComponent<RigidBody>()->UpdateRigidBody();
			player2->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_RETURN]) //resets player one position and removes forces applied to rigid body
		{
			player1->GetComponent<RigidBody>()->Get()->clearForces();
			player1->GetTransform()->SetPosition(player1Start + glm::vec3(30, 0, 0));
			btVector3 zeroVector(0, 0, 0);
			player1->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player1->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			//b->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));
				
		}

		if (currentKeyStates[SDL_SCANCODE_SPACE] && isGroundedPlayer2 && !player2Frozen) //player2 jump
		{
			player2->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 5.f, 0.f));
			//b->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));

		}

		if (currentKeyStates[SDL_SCANCODE_KP_0] && isGrounded && !player1Frozen) //player1 jump
		{
			player1->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 5.f, 0.f));
			//b->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));

		}

		if (currentKeyStates[SDL_SCANCODE_R]) //reset player2 position
		{
			player2->GetComponent<RigidBody>()->Get()->clearForces();
			player2->GetTransform()->SetPosition(player2Start + glm::vec3(30, 0, 0));
			btVector3 zeroVector(0, 0, 0);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
		}

		if (currentKeyStates[SDL_SCANCODE_Z] && currentKeyStates[SDL_SCANCODE_BACKSPACE]) //reset ball 
		{
			
			ball->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			ball->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			ball->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			ball->GetTransform()->SetPosition(ballStart);
		}

		if (currentKeyStates[SDL_SCANCODE_ESCAPE]) //quit
		{

			Quit();
		}
		


		SDL_GL_SwapWindow(m_window);

	}
}

void Application::Quit()
{
	//Close SDL
	Physics::GetInstance()->Quit();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

void Application::UpdateBlueScore() //updates the scoreboard via switch case based on blueGoals variable, resets ball and starts timer to give delay before restarting game
{
	switch (blueGoals)
	{
	case 1:
		blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/oneNoHyph.obj"));
		break;
	case 2:
		blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/twoNoHyph.obj"));
		break;
	case 3:
		blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/threeNoHyph.obj"));
		break;
	case 4:
		blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/fourNoHyph.obj"));
		break;
	case 5:
		blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/fiveNoHyph.obj"));
		winningTeam->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/blueTeamWins.obj"));
		winningTeam->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/Blue.jpg"));
		//ball->GetComponent<RigidBody>()->Get()->setGravity(btVector3(0, 0, 0));
		ball->GetTransform()->AddPosition(glm::vec3(0, 900, 0));
		restartGameDelayTimer = 300;
		break;
	}
}

void Application::UpdateRedScore() //updates the scoreboard via switch case based on blueGoals variable, resets ball and starts timer to give delay before restarting game
{
	switch (redGoals)
	{
	case 1:
		redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/one1.obj"));
		break;
	case 2:
		redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/two.obj"));
		break;
	case 3:
		redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/three.obj"));
		break;
	case 4:
		redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/four.obj"));
		break;
	case 5:
		redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/five.obj"));
		winningTeam->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/redTeamWins.obj"));
		winningTeam->GetComponent<MeshRenderer>()->EditTexture(Resources::GetInstance()->GetTexture("Images/Textures/Red.jpg"));
		//ball->GetComponent<RigidBody>()->Get()->setGravity(btVector3(0, 0, 0));
		ball->GetTransform()->AddPosition(glm::vec3(0, 900, 0));
		restartGameDelayTimer = 300;
		break;
	}
}

void Application::RestartGame() //resets the game to original state
{
	redTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/one.obj"));
	blueTeamPoints->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/zeroNoHyph.obj"));
	restartGameDelayTimer = 300;
	redGoals = 0;
	blueGoals = 0;
	winningTeam->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/emptyObject.obj"));
	player1->GetTransform()->SetPosition(glm::vec3(0.f, 5.f, 60.f));
	player2->GetTransform()->SetPosition(glm::vec3(0.f, 5.f, -90.f));
	ball->GetComponent<RigidBody>()->Get()->clearForces();
	ball->GetTransform()->SetPosition(ballStart);
}


void Application::Update(float deltaTime)
{
	for (auto& a : m_entities)
	{
		a->OnUpdate(deltaTime);
		a->GetComponent<RigidBody>()->OnUpdate(deltaTime);
	}



}

void Application::Render()
{
	/* Clear context */
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_mainCamera->Recalculate();
	for (auto& a : m_entities)
	{
		a->OnRender();
		
	}
}


Application::~Application()
{

}



Application * Application::GetInstance()
{
	if (m_application == nullptr)
	{
		m_application = new Application();
	}
	return m_application;
}

void Application::Run()
{
	Init();
	Loop();
	Quit();
}

void Application::SetCamera(Camera* camera)
{
	if (camera != nullptr)
	{
		m_mainCamera = camera;
		//std::cout << "CAMERA" << std::endl;
	}
}

void Application::ChangeCamera(Camera* camera)
{
	
		m_mainCamera = camera;


		//std::cout << "CAMERA" << std::endl;
	
}

/*void Application::SetCameraType(CameraType* camera)
{
	if (camera != nullptr)
	{
		camera = CameraType::PERSPECTIVE
	}
}*/
