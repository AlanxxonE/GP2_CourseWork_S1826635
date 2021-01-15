#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems(); //initialise all the fundamental systems
	void initTransforms(); //initialise all the starting transform values of the meshes
	void processInput(); //method that handles the inputs while also checking for game states
	void gameLoop(); //loop that performs recurring methods until the game is over
	void drawGame(); //method that draws the meshes and textures on screen based on their transform positions
	void CameraMovement(); //method that lets the user move forward&backwards or rotate the camera based on the keyboard inputs
	void MeshMovement(); //method that lets the user move the mesh left or right based on the keyboard inputs
	void TreeMovement(); //methods that manages automatically how the tree should behave by making the mesh move and change positions

	//method that loads up in the console window, before the game loop method is executed, in order to show the game instructions
	void GameInstructions(); 

	//method that checks if a collision happened between two mesh spheres
	//parameters: first mesh sphere position, first mesh sphere radius, second mesh sphere position, second mesh sphere radius
	bool CheckCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	//method that executes an audio using a playSound call from the audio device
	//parameters: ID of the audio source, the vector position where the audio will be executed
	void playAudio(unsigned int Source, glm::vec3 pos);

	Display _gameDisplay;
	GameState _gameState;
	Mesh wpMesh, bgMesh, trMesh, lfMesh;
	Camera myCamera;
	Texture woodpeckerTexture, backgroundTexture, treeTexture, fallTexture;
	Shader shader;
	Audio audioDevice;

	int treePos; //the variable that holds the different positions the tree can spawn upon

	//the variables that dictates the rate of the falling speed of the leaves
	//the speed of the incoming tree and how many points the player gains based on how much time passes avoiding ostacles 
	float treeSpeed, fallSpeed, flyScore; 

	float moveCameraZ; //the value for the camera movement
	float rotateCameraX; //the value for the camera rotation
	float moveMeshX; //the value of the mesh movement
	unsigned int bgMusic; //the ID of the audio source
};

