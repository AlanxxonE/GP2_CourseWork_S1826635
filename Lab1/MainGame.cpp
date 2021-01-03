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

	Vertex vertices[] = { Vertex(glm::vec3(-1, -1, 0)), Vertex(glm::vec3(0, 1, 0)), Vertex(glm::vec3(1, -1, 0)) }; //array of vertices defined by their positions

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //create new Mesh, size calcuated by number of bytes of an array
	Shader shader("..\\res\\shader"); //create new Shader

	shader.Bind(); //bind the shader
	mesh.Draw(); //draw the mesh

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