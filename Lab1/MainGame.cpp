#include "MainGame.h"
#include <iostream>
#include <string>
#include <Windows.h>

unsigned int indices[] = { 0, 1, 2 };
Transform woodpeckerTransform, treeTransform, /*backgroundTransformOne, backgroundTransformTwo,*/ fallTransform, fallTransformOne, fallTransformTwo;

MainGame::MainGame()
{
	_gameState = GameState::PLAY; //sets the gamestate to PLAY
	Display* _gameDisplay = new Display(); //new display
	Shader shader();
	Shader fog();
	Shader toon();
	Shader rim();
	Shader geo();
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

	bgMusic = audioDevice.loadSound("..\\res\\Forest.wav"); //loads in the background music, music loaded: Forest Ambience

	wpMesh.loadModel("..\\res\\Woodpecker.obj"); //load 3D model from file, model loaded: Bird Woodpecker

	//bgMesh.loadModel("..\\res\\Background.obj"); //load 3D model from file, model loaded: Background Poster

	trMesh.loadModel("..\\res\\Tree.obj"); //load 3D model from file, model loaded: Leafless Maple Tree

	lfMesh.loadModel("..\\res\\Leaf.obj"); //load 3D model from file, model loaded: Maple Leaf

	//set mesh radius when initialaising systems to avoid updating in every loop round
	wpMesh.SetSphereRad(100);
	trMesh.SetSphereRad(100);

	woodpeckerTexture.init("..\\res\\feather.jpg"); //initialise a texture loading it from folder, texture loaded: Black Feathers
	//backgroundTexture.init("..\\res\\leaf.jpg"); //initialise a texture loading it from folder, texture loaded: Background Forest Leaves
	treeTexture.init("..\\res\\bark.jpg"); //initialise a texture loading it from folder, texture loaded: Maple Tree Bark
	fallTexture.init("..\\res\\fall.jpg"); //initialise a texture loading it from folder, texture loaded: Red Maple Falling Leaf

	shader.init("..\\res\\shader.vert", "..\\res\\shader.frag"); //initialise new shader

	fog.init("..\\res\\shaderFog.vert", "..\\res\\shaderFog.frag"); //initialise fog shader

	toon.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //initialise toon shader

	rim.init("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag"); //initialise rim shader

	geo.initGeo(); //initialise geo shader

	emap.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");

	vector<std::string> faces
	{
		"..\\res\\skybox\\forestRightV2.jpg",
		"..\\res\\skybox\\forestLeftV2.jpg",
		"..\\res\\skybox\\forestTopV2.jpg",
		"..\\res\\skybox\\forestBottomV2.jpg",
		"..\\res\\skybox\\forestFrontV2.jpg",
		"..\\res\\skybox\\forestBackV2.jpg"
	};

	skyBox.init(faces);

	flyScore = 0; //assign the starting fly score value

	treePos = 0; //assign the starting tree mesh position

	treeSpeed = 200; //assign the initial tree speed mesh value

	fallSpeed = 40; //assign the initial falling leaf mesh value

	initTransforms(); //initialise all the starting transform values of the meshes

	rotateCameraX = 0; //assign the initial value for rotating the camera in the X axis of the forward vector of the projection
	moveCameraZ = -40; //assign the starting value of the camera vector position in the Z axis

	myCamera.initCamera(glm::vec3(0, 0, moveCameraZ), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 1000.0f); //initialise camera
}

void MainGame::initTransforms()
{
	//set the position, rotation and scale of the first background transform
	//backgroundTransformOne.SetPos(glm::vec3(100, 0, 200));
	//backgroundTransformOne.SetRot(glm::vec3(0, 1.58f, 0));
	//backgroundTransformOne.SetScale(glm::vec3(2, 3, 2));
	
	//set the position, rotation and scale of the second background transform
	//backgroundTransformTwo.SetPos(glm::vec3(-100, 0, 200));
	//backgroundTransformTwo.SetRot(glm::vec3(0, 1.58f, 0));
	//backgroundTransformTwo.SetScale(glm::vec3(2, 3, 2));

	//set the rotation and scale of the falling leaves transforms
	fallTransform.SetRot(glm::vec3(1, 1.58f, 0));
	//fallTransform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	fallTransformOne.SetRot(glm::vec3(1, 1.58f, 0));
	//fallTransformOne.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	fallTransformTwo.SetRot(glm::vec3(1, 1.58f, 0));
	//fallTransformTwo.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	//set the scale of the woodpecker transform
	woodpeckerTransform.SetScale(glm::vec3(200, 200, 200));

	//set the position of the tree transform
	treeTransform.SetScale(glm::vec3(1,2,1));
	treeTransform.SetPos(glm::vec3(0, -100, treeSpeed));
}

void MainGame::gameLoop()
{
	GameInstructions();

	while (_gameState != GameState::EXIT) //when gamestate changes to exit the while is executed no more
	{
		processInput(); //check if the game is still running and process events

		drawGame(); //method responsible for drawing textures and meshes inside the display window

		//method that constantly check if a collision happened between two specific meshes
		CheckCollision(wpMesh.GetSpherePos(), wpMesh.GetSphereRad(), trMesh.GetSpherePos(), trMesh.GetSphereRad());

		CameraMovement(); //method that handles the movements of the camera based on user inputs
		MeshMovement(); //method that handles the movements of the woodpecker mesh based on user inputs
		TreeMovement(); //method that handles the movements of the tree mesh autonomously

		//method that reproduce an audio track in a loop at a specific position
		//while also checking if the audio source is already playing, avoiding audio stack or unwanted replays
		playAudio(bgMusic, glm::vec3(0.0f, 0.0f, 0.0f)); 
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
	//Enables openGL fog function to enhance the atmosphere
	/*
	glEnable(GL_FOG);
	float fogColor[4] = { 0.8, 0.8, 0.8, 1 };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.8);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, -50);
	glFogf(GL_FOG_END, 0);
	*/

	_gameDisplay.ClearDisplay(0.2f, 0.8f, 0.5f, 1.0f); //clears the display while also assigning a light green color

	//binds the shader, updates it with the woodpecker transform information
	//binds the woodpecker texture, draws the bird mesh and sets the collision sphere based on the transform position
	geo.Bind();

	SetGeoShaderAttributes();

	geo.Update(woodpeckerTransform, myCamera);
	woodpeckerTexture.Bind(0);

	wpMesh.Draw();
	wpMesh.SetSpherePos(*woodpeckerTransform.GetPos());

	//updates the shader with the tree transform information
	//binds the tree texture, draws the maple tree mesh and sets the collision sphere based on the transform position plus an offset from the ground
	shader.Bind();

	shader.Update(treeTransform, myCamera);
	treeTexture.Bind(0);

	trMesh.Draw();
	trMesh.SetSpherePos(*treeTransform.GetPos() + glm::vec3(0, 100, 0));

	//updates the shader with the first and second background transforms information
	//binds the background leaves texture, draws the two poster meshes
	//shader.Update(backgroundTransformOne, myCamera);
	//backgroundTexture.Bind(0);

	//bgMesh.Draw();

	//shader.Update(backgroundTransformTwo, myCamera);

	//bgMesh.Draw();

	//updates the shader with the fallen leaves transforms information
	//binds the falling leaf texture, draws the three maple leaf meshes
	emap.Bind();

	SetEMapShaderAttributes();

	emap.Update(fallTransform, myCamera);
	fallTexture.Bind(0);

	lfMesh.Draw();

	SetEMapShaderAttributes1();

	emap.Update(fallTransformOne, myCamera);

	lfMesh.Draw();

	SetEMapShaderAttributes2();

	emap.Update(fallTransformTwo, myCamera);

	lfMesh.Draw();

	DrawSkyBox();

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
			moveCameraZ -= 0.1f; //down arrow key for moving the camera backwards
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (moveCameraZ < -25)
		{
			moveCameraZ += 0.1f; //up arrow key for moving the camera forwards
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (rotateCameraX > -5)
		{
			rotateCameraX -= 0.01f; //right arrow key to rotate the camera right
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (rotateCameraX < 5)
		{
			rotateCameraX += 0.01f; //left arrow key to rotate the camera left
		}
	}

	//camera methods to update the new position and rotation of the camera
	myCamera.moveCamera(glm::vec3(0.0f, 0.0f, moveCameraZ));
	myCamera.rotateCamera(glm::vec3(rotateCameraX, 0.0f, 1.0f));
}

void MainGame::MeshMovement()
{
	//Keyboard Inputs for moving the mesh model
	if (GetAsyncKeyState('D'))
	{
		if (moveMeshX > -10.0f)
		{
			moveMeshX -= 0.1f; //D letter key to move the woodpecker to the right
		}
	}

	if (GetAsyncKeyState('A'))
	{
		if (moveMeshX < 10.0f)
		{
			moveMeshX += 0.1f; //A letter key to move the woorpecker to the left
		}
	}

	//transform method to update the new woodpecker mesh position
	woodpeckerTransform.SetPos(glm::vec3(moveMeshX, -10, 0.0f));
}

void MainGame::TreeMovement()
{
	flyScore++; //assignment that adds a point to the fly score value for every loop survived

	//checks the tree position variable value and assigns a new transform position X value to generate the tree in a different X point in space
	if (treePos == 0)
	{
		treeTransform.SetPos(glm::vec3(10, -100, treeSpeed));
	}
	else if (treePos == 1)
	{
		treeTransform.SetPos(glm::vec3(0, -100, treeSpeed));
	}
	else
	{
		treeTransform.SetPos(glm::vec3(-10, -100, treeSpeed));
	}

	//updates the tree speed value until it goes past the camera position
	//when that happens the tree position value is changed adn resets the original tree speed value
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

	//updates the fall speed value until it reaches the floor of the forest
	//the three different transforms for the different leaves are then updated
	if (fallSpeed > -20)
	{
		fallSpeed -= 0.005f;
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

void MainGame::SetFogShaderAttributes()
{
	//fog.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));

	//fog.setMat4("u_vm", myCamera.GetViewProjection());
	//fog.setMat4("u_pm", myCamera.GetViewProjection());

	fog.setFloat("minDist", treeSpeed - 200);
	fog.setFloat("maxDist", 200);
	fog.setVec3("fogColor", glm::vec3(0.2f, 0.8f, 0.5f));
}

void MainGame::SetToonShaderAttributes()
{
	toon.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::SetRimShaderAttributes()
{
	glm::vec3 camDir;
	camDir = wpMesh.GetSpherePos() - myCamera.GetPos();
	camDir = glm::normalize(camDir);
	rim.setMat4("u_pm", myCamera.GetProjection());
	rim.setMat4("u_vm", myCamera.GetView());
	rim.setMat4("model", woodpeckerTransform.GetModel());
	rim.setMat4("view", myCamera.GetView());
	rim.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::SetGeoShaderAttributes()
{
	//float randX = ((float)rand() / (RAND_MAX));
	//float randY = ((float)rand() / (RAND_MAX));
	//float randZ = ((float)rand() / (RAND_MAX));

	// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	//geo.setFloat("randColourX", randX);
	//geo.setFloat("randColourY", randY);
	//geo.setFloat("randColourZ", randZ);

	// Geom: uniform float time;
	geo.setFloat("time", treeSpeed/10);
}

void MainGame::SetEMapShaderAttributes()
{
	emap.setMat4("projection", myCamera.GetProjection());
	emap.setMat4("view", myCamera.GetView());
	emap.setMat4("model", fallTransformOne.GetModel());
	emap.setVec3("cameraPos", myCamera.GetPos());
}

void MainGame::SetEMapShaderAttributes1()
{
	emap.setMat4("projection", myCamera.GetProjection());
	emap.setMat4("view", myCamera.GetView());
	emap.setMat4("model", fallTransform.GetModel());
	emap.setVec3("cameraPos", myCamera.GetPos());
}

void MainGame::SetEMapShaderAttributes2()
{
	emap.setMat4("projection", myCamera.GetProjection());
	emap.setMat4("view", myCamera.GetView());
	emap.setMat4("model", fallTransformTwo.GetModel());
	emap.setVec3("cameraPos", myCamera.GetPos());
}

void MainGame::DrawSkyBox()
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.textureID);

	skyBox.draw(&myCamera);
}

void MainGame::GameInstructions()
{
	//displays on the console log all the intructions to play the game just before the display window is loaded

	cout << "\n" << "WELCOME TO 'FOREST FLIGHT'" << "\n";

	cout << "\n" << "Ready to start flying?!" << "\n";

	cout << "\n" << "A & D to fly Left and Right respectively!" << "\n";

	cout << "\n" << "UP & DOWN arrow keys to focus the Woodpecker eyesight!" << "\n";

	cout << "\n" << "LEFT & RIGHT arrow keys to see the Woodpecker peripheral view!" << "\n";

	cout << "\n" << "Avoid hitting the trees or the Woodpecker will faint!" << "\n";
}

bool MainGame::CheckCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance * distance < (m1Rad + m2Rad)) //check if the distance of the two mesh sphere colliders collided
	{
		//if that is the case, the collision is detected, the game closes by changing the game state to EXIT
		//the Game Over is dictated and the total fly score is displayed on the console window
		cout << "\n" << "COLLISION DETECTED" << "\n";

		_gameState = GameState::EXIT;

		cout << "\n" << "GAME OVER!" << "\n";

		cout << "\n" << "Your fly Score was:  " << flyScore << "\n";

		return true;
	}
	else
	{
		//otherwise no collision is returned
		return false;
	}
}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	ALint state;

	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/

	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos); //plays a specific audio track based on the audio source and the vector position
	}
}
