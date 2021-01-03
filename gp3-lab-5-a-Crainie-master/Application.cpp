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













//SDL_Surface* surface;
Application *Application::m_application = nullptr;
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
Entity* a = new Entity();
Entity* b = new Entity(glm::vec3(0.f, 5.f, 60.f), glm::quat({ 0, 0, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));
Entity* c = new Entity(glm::vec3(0.f, 0.f, -20.f), glm::quat({ 0, 0, 0 }), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.f, 0.f, 5.f));
Entity* d = new Entity(glm::vec3(0.f, -10.f, -100.f), glm::quat({ 0, 0, 0 }), glm::vec3(5.1f, 5.1f, 5.1f), glm::vec3(0.f, 0.f, 5.f));
Entity* e = new Entity(glm::vec3(0.f, -10.f, 70.f), glm::quat({ 0, 160.3f, 0 }), glm::vec3(5.1f, 5.1f, 5.1f), glm::vec3(0.f, 0.f, 5.f));
Entity* f = new Entity(glm::vec3(0.f, -10.f, 100.f), glm::quat({ 0, 0, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* g = new Entity(glm::vec3(0.f, -10.f, -140.f), glm::quat({ 0, 0, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* h = new Entity(glm::vec3(80.f, -10.f, -120.f), glm::quat({ 0, 20.4f, 0 }), glm::vec3(80.1f, 40.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* i = new Entity(glm::vec3(-100.f, -10.f, -120.f), glm::quat({ 0, 20.4f, 0 }), glm::vec3(80.1f, 15.1f, 10.1f), glm::vec3(0.f, 0.f, 0.f));
Entity* player2 = new Entity(glm::vec3(0.f, 5.f, -60.f), glm::quat({ 0, 0, 0 }), glm::vec3(10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, 5.f));




glm::vec3 player1Start = glm::vec3(0.f, 5.f, 60.f);
glm::vec3 player2Start = glm::vec3(0.f, 5.f, -80.f);
glm::vec3 ballStart = glm::vec3(0, 0, -20.f);
float cameraDistance = 10.f;
SDL_Event event;
CameraComp* cc = new CameraComp();
glm::vec3 ballX;
const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

Application::Application()
{
}



void Application::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() < 0)
	{
		printf("NOOOOOOOOO");
	}
	
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
	m_window = SDL_CreateWindow("GP3-LAB-5", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight,
		SDL_WINDOW_OPENGL);
	m_renderTarget = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	TTF_Font *font = TTF_OpenFont("COMICATE.ttf", 20);
	SDL_Color color = { 144, 77, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "i work yes", color);
	SDL_Texture *text = SDL_CreateTextureFromSurface(m_renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	SDL_RenderCopy(m_renderTarget, text, NULL, &textRect);
	SDL_RenderPresent(m_renderTarget);

	SDL_CaptureMouse(SDL_TRUE);

	OpenGlInit();
	GameInit();
	//gitHub test
	
}

void Application::drawBitmapText(const char* string, float x, float y, float z)
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

}*/

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
		soundList = { "theme", "click", "blueGoal", "redGoal" };
		soundTypes = { soundType::music, soundType::sfx, soundType::sfx, soundType::sfx };
		soundsToUse = { ASSET_AUDIO_PATH_Theme + "synth9.mp3", ASSET_AUDIO_PATH_SFX + "ClickOn.wav", ASSET_AUDIO_PATH_SFX + "blueTeamGoal.wav", ASSET_AUDIO_PATH_SFX + "redTeamGoal.wav"};
		for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
		{
			theSoundMgr -> add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
		}
		// Play the theme on a constant loop
		theSoundMgr->getSnd("theme")->play(-1);
	}
	//loading all resources
	Resources::GetInstance()->AddModel("Models/cube.obj");
	Resources::GetInstance()->AddModel("Models/portal.obj");
	Resources::GetInstance()->AddModel("Models/cube2.obj");
	Resources::GetInstance()->AddModel("Models/football.obj");
	Resources::GetInstance()->AddModel("Models/hockeyGoal2.obj");
	Resources::GetInstance()->AddModel("Models/wall.obj");
	Resources::GetInstance()->AddModel("Models/goals.obj");
	Resources::GetInstance()->AddModel("Models/footballBoot3.obj");
	Resources::GetInstance()->AddModel("Models/footballBoot4.obj");
	Resources::GetInstance()->AddTexture("Images/Textures/Wood.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Gold.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Ice.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Silver.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/road.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/grass.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/leather.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/wall.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Sapphire.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/Ruby.jpg");
	Resources::GetInstance()->AddTexture("Images/Textures/football.jpg");
	Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/simple_VERT.glsl", 
		ASSET_PATH + "Shaders/simple_FRAG.glsl"), 
		"simple"
		
	);

	
	m_entities.push_back(a);
	a->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/cube.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/grass.jpg"))
	);
	MeshRenderer* m = a->GetComponent<MeshRenderer>();
	a->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	a->AddComponent<RigidBody>();
	a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 150.f)));
	a->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	a->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 150.f));
	a->GetComponent<RigidBody>()->Get()->setFriction(1);
	//a->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(d);
	d->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/goals.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Gold.jpg"))
	);
	MeshRenderer* p = d->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	d->AddComponent<RigidBody>();
	d->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(13.f, 5.f, 0.05f)));
	d->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	d->GetComponent<RigidBody>()->Get()->setFriction(1);
	d->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(f);
	f->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* r = f->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	f->AddComponent<RigidBody>();
	f->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 30.f, 1.f)));
	f->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	f->GetComponent<RigidBody>()->Get()->setFriction(1);
	f->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(g);
	g->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* s = g->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	g->AddComponent<RigidBody>();
	g->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 30.f, 1.f)));
	g->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	g->GetComponent<RigidBody>()->Get()->setFriction(1);
	g->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(h);
	h->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* t = h->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	h->AddComponent<RigidBody>();
	h->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(300.f, 30.f, 5.f)));
	h->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	h->GetComponent<RigidBody>()->Get()->setFriction(1);
	h->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(i);
	i->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/wall.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/wall.jpg"))
	);
	MeshRenderer* u = i->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	i->AddComponent<RigidBody>();
	i->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(300.f, 30.f, 5.f)));
	i->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	i->GetComponent<RigidBody>()->Get()->setFriction(1);
	i->GetComponent<RigidBody>()->Get()->setRestitution(1);

	m_entities.push_back(e);
	e->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/goals.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Gold.jpg"))
	);
	MeshRenderer* q = e->GetComponent<MeshRenderer>();
	//d->GetTransform()->SetPosition(glm::vec3(0, -10.f, -20.f));
	e->AddComponent<RigidBody>();
	e->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(13.f, 5.f, -0.05f)));
	e->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	e->GetComponent<RigidBody>()->Get()->setFriction(1);
	e->GetComponent<RigidBody>()->Get()->setRestitution(1);
	

	
	m_entities.push_back(b);
	b->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/footballBoot3.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Sapphire.jpg"))
	);
	MeshRenderer* n = b->GetComponent<MeshRenderer>();
	//b->GetTransform()->SetPosition(glm::vec3(10.f, 0.f, -30.f));
	b->AddComponent<RigidBody>();
	b->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.f, 1.f, 5.f)));
	b->GetComponent<RigidBody>()->Get()->setFriction(1);
	b->GetComponent<RigidBody>()->Get()->setSpinningFriction(1);
	b->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0));
	//b->GetComponent<RigidBody>()->Get()->setRollingFriction(1);
	b->GetComponent<RigidBody>()->Get()->setRestitution(1);
	
	//b->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	//b->GetTransform()->SetScale(glm::vec3(10.f, 10.f, 10.f));

	m_entities.push_back(player2);
	player2->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/footballBoot4.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Ruby.jpg"))
	);
	MeshRenderer* v = player2->GetComponent<MeshRenderer>();
	//b->GetTransform()->SetPosition(glm::vec3(10.f, 0.f, -30.f));
	player2->AddComponent<RigidBody>();
	player2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.f, 1.f, 5.f)));
	player2->GetComponent<RigidBody>()->Get()->setFriction(1);
	player2->GetComponent<RigidBody>()->Get()->setSpinningFriction(1);
	player2->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0));
	//b->GetComponent<RigidBody>()->Get()->setRollingFriction(1);
	player2->GetComponent<RigidBody>()->Get()->setRestitution(1);
	//b->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	//b->GetTransform()->SetScale(glm::vec3(10.f, 10.f, 10.f));
	
	m_entities.push_back(c);
	c->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/football.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/football.jpg"))
	);
	MeshRenderer* o = c->GetComponent<MeshRenderer>();
	//c->GetTransform()->SetPosition(glm::vec3(20.f, 0.f, 0.f));
	//c->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	c->AddComponent<RigidBody>();
	//c->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(10.f, 1.f, 10.f)));
	c->GetComponent<RigidBody>()->Init(new SphereShape(0.6));
	c->GetComponent<RigidBody>()->Get()->setFriction(0.1);
	c->GetComponent<RigidBody>()->Get()->setRollingFriction(0.1);
	c->GetComponent<RigidBody>()->Get()->setRestitution(1);
	c->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0.f, 0, 0.f));
	//c->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	//btCompoundShape* compound = new btCompoundShape();
	//btTransform localTrans;
	//localTrans.setIdentity();
	//localTrans.setOrigin(btVector3(0, 10, 10));
	//compound->addChildShape(localTrans, c->GetComponent<RigidBody>()->Get()->getCollisionShape());
	new MeshRenderer(
		Resources::GetInstance()->GetModel("Models/portal.obj"),
		Resources::GetInstance()->GetShader("simple"),
		Resources::GetInstance()->GetTexture("Images/Textures/football.jpg"));
	
	
	
	

	for (int i = 0; i < 10; i++)
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

	//b = new Entity();
	//m_entities.push_back(b);
	
	b->AddComponent(cc);
	cc->Start();
	

	

	



	

	Resources::GetInstance()->ReleaseUnusedResources();

}

void Application::Loop()
{
	
	m_appState = AppState::RUNNING;
	std::cout << playerX << std::endl;
	auto prevTicks = std::chrono::high_resolution_clock::now();
	b->GetComponent<RigidBody>()->UpdateParent();
	b->GetComponent<RigidBody>()->UpdateRigidBody();
	c->GetComponent<RigidBody>()->UpdateParent();
	c->GetComponent<RigidBody>()->UpdateRigidBody();
	ballX = b->GetTransform()->GetPosition();

	while (m_appState != AppState::QUITTING)
	{
		
		if (Physics::GetInstance()->Collision3D(b->GetComponent<RigidBody>()->Get(), 0, 0, c->GetComponent<RigidBody>()->Get(), 1, 1) == true)
		{
			std::cout << "HERE" << std::endl;
			//c->GetTransform()->SetPosition(glm::vec3(b->GetTransform()->GetPosition.x,);
			//ballAttached = true;
			

		}

		if (Physics::GetInstance()->Collision3D(b->GetComponent<RigidBody>()->Get(), 0, 0, a->GetComponent<RigidBody>()->Get(), 1, 1) == true)
		{
			//std::cout << "ground" << std::endl;
			isGrounded = true;
		}

		if (!Physics::GetInstance()->Collision3D(b->GetComponent<RigidBody>()->Get(), 0, 0, a->GetComponent<RigidBody>()->Get(), 1, 1) == true)
		{
			//std::cout << "ground" << std::endl;
			isGrounded = false;
		}

		if (Physics::GetInstance()->Collision3D(c->GetComponent<RigidBody>()->Get(), 0, 0, d->GetComponent<RigidBody>()->Get(), 1, 1) == true)
		{
			std::cout << "player1 Goal" << std::endl;
			b->GetTransform()->SetPosition(player1Start);
			player2->GetTransform()->SetPosition(player2Start);
			c->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			b->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			b->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			c->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			c->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			theSoundMgr->getSnd("blueGoal")->play(0);
			c->GetTransform()->SetPosition(ballStart);
			
		}

		if (Physics::GetInstance()->Collision3D(c->GetComponent<RigidBody>()->Get(), 0, 0, e->GetComponent<RigidBody>()->Get(), 1, 1) == true)
		{
			std::cout << "player2 Goal" << std::endl;
			b->GetTransform()->SetPosition(player1Start);
			player2->GetTransform()->SetPosition(player2Start);
			c->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			b->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			b->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			c->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			c->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			theSoundMgr->getSnd("redGoal")->play(0);
			c->GetTransform()->SetPosition(ballStart);
			//isGrounded = false;
		}

		//if (ballAttached == true)
		//{
			//AttachBallPlayer1();
		//}

		

		//poll SDL events
		while (SDL_PollEvent(&event))
		{

			b->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.5));
			player2->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.5));
			c->GetComponent<RigidBody>()->Get()->applyDamping(btScalar(0.1f));
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
				case SDLK_a:
					if (modifyControls == false) 
					{
						
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-3.0f, 0.f, 0.f)); 
						
					}
					if(modifyControls == true) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -3.f));
						
					}
					//b->GetComponent<RigidBody>()->UpdateRigidBody();
					//b->GetComponent<RigidBody>()->UpdateParent();
					break;
				case SDLK_d:
					if (modifyControls == false) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(3.0f, 0.f, 0.f)); 
					}
					if(modifyControls == true) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.0f, 0.f, 3.f));
					}
					//b->GetComponent<RigidBody>()->UpdateRigidBody();
					//b->GetComponent<RigidBody>()->UpdateParent();
					break;
				case SDLK_s:
					if (modifyControls == false) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, 3.f));
						//output(50, 50, 1, 1, 1, "Hello Friends");
					}
					if (modifyControls == true) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-3.f, 0.f, 0.f));
					}
					//b->GetTransform()->AddPosition(glm::vec3(0.0f, 0.f, 1.f));		
					//b->GetComponent<RigidBody>()->UpdateRigidBody();
					//b->GetComponent<RigidBody>()->UpdateParent();
					break;
				case SDLK_w:
					if (modifyControls == false) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 0.f, -3.f), btVector3(0, 0, 0)); 
					}
					if (modifyControls == true) 
					{ 
						//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(3.f, 0.f, 0.f), btVector3(0, 0, 0)); 
					}
					//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 0.f, -4.f), btVector3(0, 0, 0));
					//b->GetComponent<RigidBody>()->UpdateRigidBody();
					//b->GetComponent<RigidBody>()->UpdateParent();
					break;
				case SDLK_SPACE:
					
					//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 10.f, 0.f), btVector3(0, 0, 0));
					if (isGrounded == true) { b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 10.f, 0.f)); }
					//m_mainCamera->tester();
					break;

				case SDLK_TAB:
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
				case SDLK_c:
					if (thirdPerson == true)
					{
						
						a->AddComponent(cc);
						cc->Start2();
						thirdPerson = false;
						m_mainCamera->DifferentCameraView();
						modifyControls = true;
						break;
					}

					else
					{
						b->AddComponent(cc);
						cc->Start();
						thirdPerson = true;
						modifyControls = false;
						break;
					}
				case SDLK_i:
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
					b->GetComponent<RigidBody>()->UpdateRigidBody();
					
					break;
				}
			
				
			//record when the user releases a key
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
				SDL_SetRelativeMouseMode(SDL_TRUE);
				if (SDL_GetRelativeMouseMode() == true)
				{
					b->GetComponent<CameraComp>()->yaw += 7 * event.motion.xrel * m_worldDeltaTime;
					b->GetComponent<CameraComp>()->pitch += 7 * event.motion.yrel * m_worldDeltaTime;
					if (b->GetComponent<CameraComp>()->pitch > AI_MATH_TWO_PI_F)
					{
						b->GetComponent<CameraComp>()->pitch = AI_MATH_TWO_PI_F - 0.1f;
						//printf("working1");
					}

					if (b->GetComponent<CameraComp>()->pitch < AI_MATH_TWO_PI_F)
					{
						b->GetComponent<CameraComp>()->pitch = -AI_MATH_TWO_PI_F + 0.1f;
						//printf("working2");
					}

					float forX = -sin(b->GetComponent<CameraComp>()->yaw) * cos(b->GetComponent<CameraComp>()->pitch);
					float forY = -sin(b->GetComponent<CameraComp>()->pitch);
					float forZ = -cos(b->GetComponent<CameraComp>()->yaw) * cos(b->GetComponent<CameraComp>()->pitch);
					b->GetTransform()->setForward(glm::vec3(forX, forY, forZ));

					float rX = -cos(b->GetComponent<CameraComp>()->yaw);
					float rY = 0.0f;
					float rZ = sin(b->GetComponent<CameraComp>()->yaw);
					b->GetTransform()->setRight(glm::vec3(rX, rY, rZ));
					
					b->GetTransform()->setUp(glm::cross(b->GetTransform()->GetForward(), b->GetTransform()->GetRight()));
					
					b->GetTransform()->setForward(glm::normalize(b->GetTransform()->GetForward()));
					b->GetTransform()->setRight(glm::normalize(b->GetTransform()->GetRight()));
					b->GetTransform()->setUp(glm::normalize(b->GetTransform()->GetUp()));
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
		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			
			if (modifyControls == false)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.0f, 0.f, 0.f)); 
			}
			if (modifyControls == true)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.0f, 0.f, 1.f));
			}
			b->GetComponent<RigidBody>()->UpdateRigidBody();
			b->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			if (modifyControls == false)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-1.0f, 0.f, 0.f)); 

			}
			if (modifyControls == true)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -1.f));
				

			}
			b->GetComponent<RigidBody>()->UpdateRigidBody();
			b->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			if (modifyControls == false)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, -1.f));
			}
			if (modifyControls == true)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(1.f, 0.f, 0.f));
			}
			//b->GetComponent<RigidBody>()->Get()->applyImpulse(btVector3(0.f, 0.f, -4.f), btVector3(0, 0, 0));
			b->GetComponent<RigidBody>()->UpdateRigidBody();
			b->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			if (modifyControls == false)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(0.f, 0.f, 1.5f));
			}
			if (modifyControls == true)
			{
				b->GetComponent<RigidBody>()->Get()->applyCentralImpulse(btVector3(-1.5f, 0.f, 0.f));
			}
			//b->GetTransform()->AddPosition(glm::vec3(0.0f, 0.f, 1.f));		
			b->GetComponent<RigidBody>()->UpdateRigidBody();
			b->GetComponent<RigidBody>()->UpdateParent();
		}

		if (currentKeyStates[SDL_SCANCODE_D])
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

		if (currentKeyStates[SDL_SCANCODE_A])
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

		if (currentKeyStates[SDL_SCANCODE_W])
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

		if (currentKeyStates[SDL_SCANCODE_S])
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

		if (currentKeyStates[SDL_SCANCODE_RETURN])
		{
			b->GetComponent<RigidBody>()->Get()->clearForces();
			b->GetTransform()->SetPosition(player1Start + glm::vec3(30, 0, 0));
			btVector3 zeroVector(0, 0, 0);
			b->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			b->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			b->GetComponent<MeshRenderer>()->EditMesh(Resources::GetInstance()->GetModel("Models/portal.obj"));
				
		}

		if (currentKeyStates[SDL_SCANCODE_R])
		{
			player2->GetComponent<RigidBody>()->Get()->clearForces();
			player2->GetTransform()->SetPosition(player2Start + glm::vec3(30, 0, 0));
			btVector3 zeroVector(0, 0, 0);
			player2->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			player2->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
		}

		if (currentKeyStates[SDL_SCANCODE_Z] && currentKeyStates[SDL_SCANCODE_BACKSPACE])
		{
			
			c->GetComponent<RigidBody>()->Get()->clearForces();
			btVector3 zeroVector(0, 0, 0);
			c->GetComponent<RigidBody>()->Get()->setLinearVelocity(zeroVector);
			c->GetComponent<RigidBody>()->Get()->setAngularVelocity(zeroVector);
			c->GetTransform()->SetPosition(ballStart);
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

void Application::AttachBallPlayer1()
{
	
	
		c->GetTransform()->SetPosition(glm::vec3(ballX.x, ballX.y + 5, ballX.z + 40));
		ballAttached = false;
	
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
