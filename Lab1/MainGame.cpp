#include "MainGame.h"
#include <iostream>
#include <string>
#include <Windows.h>

unsigned int indices[] = { 0, 1, 2 };
Transform woodpeckerTransform, treeTransform, backgroundTransformOne, backgroundTransformTwo, fallTransform, fallTransformOne, fallTransformTwo;

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

	wpMesh.loadModel("..\\res\\Woodpecker.obj"); //load 3D model from file

	bgMesh.loadModel("..\\res\\Background.obj");

	trMesh.loadModel("..\\res\\Tree.obj");

	lfMesh.loadModel("..\\res\\Leaf.obj");

	//set mesh radius when initialaising systems to avoid updating in every loop round
	wpMesh.SetSphereRad(100);
	trMesh.SetSphereRad(100);

	woodpeckerTexture.init("..\\res\\feather.jpg"); //
	backgroundTexture.init("..\\res\\leaf.jpg");
	treeTexture.init("..\\res\\bark.jpg");
	fallTexture.init("..\\res\\fall.jpg");

	shader.init("..\\res\\shader"); //new shader

	backgroundTransformOne.SetPos(glm::vec3(100, 0, 200));
	backgroundTransformOne.SetRot(glm::vec3(0, 1.58f, 0));
	backgroundTransformOne.SetScale(glm::vec3(2, 3, 2));

	backgroundTransformTwo.SetPos(glm::vec3(-100, 0, 200));
	backgroundTransformTwo.SetRot(glm::vec3(0, 1.58f, 0));
	backgroundTransformTwo.SetScale(glm::vec3(2, 3, 2));

	fallTransform.SetRot(glm::vec3(1, 1.58f, 0));
	fallTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	fallTransformOne.SetRot(glm::vec3(1, 1.58f, 0));
	fallTransformOne.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	fallTransformTwo.SetRot(glm::vec3(1, 1.58f, 0));
	fallTransformTwo.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	woodpeckerTransform.SetScale(glm::vec3(20, 20, 20));

	flyScore = 0;

	treePos = 0;

	treeSpeed = 200;

	fallSpeed = 40;

	treeTransform.SetPos(glm::vec3(0, -30, treeSpeed));

	rotateCameraX = 0;
	moveCameraZ = -40;

	myCamera.initCamera(glm::vec3(0, 0, moveCameraZ), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 1000.0f); //initialise camera
}

void MainGame::gameLoop()
{
	GameInstructions();

	while (_gameState != GameState::EXIT) //when gamestate changes to exit the while is executed no more
	{
		processInput();
		drawGame();
		CheckCollision(wpMesh.GetSpherePos(), wpMesh.GetSphereRad(), trMesh.GetSpherePos(), trMesh.GetSphereRad());
		CameraMovement();
		MeshMovement();
		TreeMovement();
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
	glFogf(GL_FOG_START, 0);

	_gameDisplay.ClearDisplay(0.2f, 0.8f, 0.5f, 1.0f);

	shader.Bind();
	shader.Update(woodpeckerTransform, myCamera);
	woodpeckerTexture.Bind(0);

	wpMesh.Draw();
	wpMesh.SetSpherePos(*woodpeckerTransform.GetPos());

	shader.Update(treeTransform, myCamera);
	treeTexture.Bind(0);

	trMesh.Draw();
	trMesh.SetSpherePos(*treeTransform.GetPos() + glm::vec3(0, +30, 0));

	shader.Update(backgroundTransformOne, myCamera);
	backgroundTexture.Bind(0);

	bgMesh.Draw();

	shader.Update(backgroundTransformTwo, myCamera);

	bgMesh.Draw();

	shader.Update(fallTransform, myCamera);
	fallTexture.Bind(0);

	lfMesh.Draw();

	shader.Update(fallTransformOne, myCamera);

	lfMesh.Draw();

	shader.Update(fallTransformTwo, myCamera);

	lfMesh.Draw();

	//previous clear display
	//_gameDisplay.ClearDisplay(); //method that clears the display

	//transform.SetPos(glm::vec3(sinf(counter), 0.0, sinf(counter) * 10));
	//transformTwo.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	//transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

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
		if (moveCameraZ > -50)
		{
			moveCameraZ -= 0.1f;
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (moveCameraZ < -25)
		{
			moveCameraZ += 0.1f;
		}
	}

	//if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	if (rotateCameraX > -0.5f)
	//	{
	//		rotateCameraX -= 0.01f;
	//	}
	//}

	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	if (rotateCameraX < 0.5f)
	//	{
	//		rotateCameraX += 0.01f;
	//	}
	//}

	//camera methods
	myCamera.moveCamera(glm::vec3(0.0f, 0.0f, moveCameraZ));
	myCamera.rotateCamera(glm::vec3(rotateCameraX, 0.0f, 1.0f));
}

void MainGame::MeshMovement()
{
	//Keyboard Inputs for moving and rotating the mesh model
	if (GetAsyncKeyState('D'))
	{
		if (moveMeshX > -10.0f)
		{
			moveMeshX -= 0.1f;
		}
	}

	if (GetAsyncKeyState('A'))
	{
		if (moveMeshX < 10.0f)
		{
			moveMeshX += 0.1f;
		}
	}

	//transform methods
	woodpeckerTransform.SetPos(glm::vec3(moveMeshX, -10, 0.0f));
}

void MainGame::TreeMovement()
{
	flyScore++;

	if (treePos == 0)
	{
		treeTransform.SetPos(glm::vec3(10, -40, treeSpeed));
	}
	else if (treePos == 1)
	{
		treeTransform.SetPos(glm::vec3(0, -40, treeSpeed));
	}
	else
	{
		treeTransform.SetPos(glm::vec3(-10, -40, treeSpeed));
	}

	if (treeSpeed > -50)
	{
		treeSpeed -= 0.1f;
	}
	else
	{
		switch (treePos)
		{
		case 0:
			treePos = 1;

			break;

		case 1:
			treePos = 2;

			break;

		case 2:
			treePos = 0;

			break;

		default:
			break;
		}

		treeSpeed = 200;
	}

	if (fallSpeed > -20)
	{
		fallSpeed -= 0.01f;
	}
	else
	{
		fallSpeed = 40;
	}

	fallTransform.SetRot(glm::vec3(fallSpeed / 5, fallSpeed / 5, 0));
	fallTransform.SetPos(glm::vec3(-fallSpeed, fallSpeed, 5));

	fallTransformOne.SetRot(glm::vec3(fallSpeed / 3, 1.58f, 0));
	fallTransformOne.SetPos(glm::vec3(-20 - (fallSpeed), 3 * fallSpeed, 5));

	fallTransformTwo.SetRot(glm::vec3(-fallSpeed, 1.58f, -fallSpeed));
	fallTransformTwo.SetPos(glm::vec3(+30 - fallSpeed / 3, -5 +(fallSpeed), 5));
}

void MainGame::GameInstructions()
{
	cout << "\n" << "WELCOME TO 'FOREST FLIGHT'" << "\n";

	cout << "\n" << "Ready to start flying?!" << "\n";

	cout << "\n" << "A & D to fly Left and Right respectively!" << "\n";

	cout << "\n" << "UP & DOWN arrow keys to focus the Woodpecker eyesight!" << "\n";

	cout << "\n" << "Avoid hitting the trees or the Woodpecker will faint!" << "\n";
}

bool MainGame::CheckCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance * distance < (m1Rad + m2Rad))
	{
		cout << "\n" << "COLLISION DETECTED" << "\n";

		_gameState = GameState::EXIT;

		cout << "\n" << "GAME OVER!" << "\n";

		cout << "\n" << "Your fly Score was:  " << flyScore << "\n";

		return true;
	}
	else
	{
		return false;
	}
}
