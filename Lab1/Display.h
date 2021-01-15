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
	void ClearDisplay(); //clears the contents in the screen window
	void ClearDisplay(float r, float g, float b, float a); //advanced version of the clear display method, also lets change the color of the screen window

	float GetWidth();
	float GetHeight();

private:

	void returnError(std::string errorString); //methods that returns an error in a form of a string so it can be displayed in the console log

	SDL_GLContext sdlGlContext; //global variable to hold the context to access initDisplay() from outside
	SDL_Window* _window; //holds pointer to out window
	int _screenWidth; //specify the width of the window size
	int _screenHeight; //specify the height of the window size
};

