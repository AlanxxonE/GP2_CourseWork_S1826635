#include "MainGame.h"
#include <iostream>
#include <string>

MainGame::MainGame()
{
	_gameState = GameState::PLAY; //sets the gamestate to PLAY
	Display* _gameDisplay = new Display(); //new display
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
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) //when gamestate changes to exit the while is executed no more
	{
		processInput();
		drawGame();
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
	_gameDisplay.ClearDisplay(); //method that clears the display

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)), Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)), Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	//Red Mesh Draw
	/*
	Vertex vertices[] = { Vertex(glm::vec3(-1, -1, 0)), Vertex(glm::vec3(0, 1, 0)), Vertex(glm::vec3(1, -1, 0)) }; //array of vertices defined by their positions
	*/

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