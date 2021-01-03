#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void ClearDisplay(); //method to clear the display

private:

	void returnError(std::string errorString);

	SDL_GLContext sdlGlContext; //global variable to hold the context to access initDisplay() from outside
	SDL_Window* _window; //holds pointer to out window
	int _screenWidth; //specify the width of the window size
	int _screenHeight; //specify the height of the window size
};

