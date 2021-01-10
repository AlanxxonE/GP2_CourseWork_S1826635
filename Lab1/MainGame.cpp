#include "MainGame.h"
#include <iostream>
#include <string>
#include <Windows.h>

unsigned int indices[] = { 0, 1, 2 };
Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY; //sets the gamestate to PLAY
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); //initialise the systems
	gameLoop(); //runs the gameloop
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); //initialise the display

	mesh1.loadModel("..\\res\\monkey3.obj"); //load 3D model from file
	mesh2.loadModel("..\\res\\monkey3.obj");

	//set mesh radius when initialaising systems to avoid updating in every loop round
	mesh1.SetSphereRad(0.65f);
	mesh2.SetSphereRad(0.65f);

	texture.init("..\\res\\bricks.jpg"); //
	shader.init("..\\res\\shader"); //new shader

	counter = 0;

	rotateCameraX = 0;
	moveCameraZ = -20;

	myCamera.initCamera(glm::vec3(0, 0, moveCameraZ), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 1000.0f); //initialise camera
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) //when gamestate changes to exit the while is executed no more
	{
		processInput();
		drawGame();
		CheckCollision(mesh1.GetSpherePos(), mesh1.GetSphereRad(), mesh2.GetSpherePos(), mesh2.GetSphereRad());
		CameraMovement();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT; //if application terminates the gamestate changes to EXIT
				break;
		}
	}
	
}

void MainGame::drawGame()
{
	//previous clear display
	//_gameDisplay.ClearDisplay(); //method that clears the display

	_gameDisplay.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	//transform.SetPos(glm::vec3(sinf(counter), 0.0, sinf(counter) * 10));
	//transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	//transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.Draw();
	mesh1.SetSpherePos(*transform.GetPos());

	//transform.SetRot(glm::vec3(0.0, -counter * 5, 0.0));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh2.Draw();
	mesh2.SetSpherePos(*transform.GetPos());

	counter = counter + 0.001f;

	//Water&Brick rotating triangles
	/*
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)), Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)), Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //create new Mesh, size calcuated by number of bytes of an array
	Shader shader("..\\res\\shader"); //create new Shader
	Texture texture("..\\res\\bricks.jpg"); //load texture

	Transform transform;
	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.Bind(); //bind the shader
	shader.Update(transform);
	texture.Bind(0);
	mesh.Draw(); //draw the mesh

	Mesh mesh1(vertices, sizeof(vertices) / sizeof(vertices[0])); //create new Mesh, size calcuated by number of bytes of an array
	Shader shader1("..\\res\\shader"); //create new Shader
	Texture texture1("..\\res\\Water.jpg"); //load texture

	Transform transform1;
	transform1.SetPos(glm::vec3(cosf(-counter), 0.0, 0.0));
	transform1.SetRot(glm::vec3(0.0, 0.0, -counter * 5));
	transform1.SetScale(glm::vec3(cosf(-counter), cosf(-counter), cosf(-counter)));

	shader1.Bind(); //bind the shader
	shader1.Update(transform1);
	texture1.Bind(0);
	mesh1.Draw(); //draw the mesh

	counter = counter + 0.01f;

	*/

	//Red Mesh Draw
	/*
	Vertex vertices[] = { Vertex(glm::vec3(-1, -1, 0)), Vertex(glm::vec3(0, 1, 0)), Vertex(glm::vec3(1, -1, 0)) }; //array of vertices defined by their positions
	*/

	//Red Triangle Draw
	/*
	glEnableClientState(GL_COLOR_ARRAY); 
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);	
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);
	glEnd();
	*/

	_gameDisplay.swapBuffer(); //method that swap the buffers
}

void MainGame::CameraMovement()
{
	//Keyboard Inputs for moving and rotating the camera
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (moveCameraZ > -30)
		{
			moveCameraZ -= 0.1f;
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (moveCameraZ < -10)
		{
			moveCameraZ += 0.1f;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (rotateCameraX > -0.5f)
		{
			rotateCameraX -= 0.01f;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (rotateCameraX < 0.5f)
		{
			rotateCameraX += 0.01f;
		}
	}

	//camera methods
	myCamera.moveCamera(glm::vec3(0.0f, 0.0f, moveCameraZ));
	myCamera.rotateCamera(glm::vec3(rotateCameraX, 0.0f, 1.0f));
}

bool MainGame::CheckCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance * distance < (m1Rad + m2Rad))
	{
		cout << "COLLISION DETECTED";
		return true;
	}
	else
	{
		return false;
	}
}
