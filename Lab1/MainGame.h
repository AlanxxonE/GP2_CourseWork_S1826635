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

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void CameraMovement();
	void MeshMovement();
	void TreeMovement();

	void GameInstructions();

	bool CheckCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	void playAudio(unsigned int Source, glm::vec3 pos);

	Display _gameDisplay;
	GameState _gameState;
	Mesh wpMesh, bgMesh, trMesh, lfMesh;
	Camera myCamera;
	Texture woodpeckerTexture, backgroundTexture, treeTexture, fallTexture;
	Shader shader;
	Audio audioDevice;

	int treePos;
	float treeSpeed, fallSpeed, flyScore;
	float moveCameraZ;
	float rotateCameraX;
	float moveMeshX;
	unsigned int bgMusic;
};

