#include "Display.h"


Display::Display()
{
	_window = nullptr; //initialise to generate null access violation for debugging. 
	_screenWidth = 1024.0f; //sets the window width
	_screenHeight = 768.0f; //sets the window height
}

Display::~Display()
{
	SDL_GL_DeleteContext(sdlGlContext); //deletes the initialised global context
	SDL_DestroyWindow(_window); //destroys the window declared in the Display class
	SDL_Quit(); //quits the executable
}

void Display::returnError(std::string errorString)
{
	std::cout << errorString << std::endl; //display a specific error passed as an argument
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in; //waits for user input before exiting the application
	SDL_Quit();
}

void Display::swapBuffer()
{
	SDL_GL_SwapWindow(_window); //swap buffers
}

void Display::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)_screenWidth, (int)_screenHeight, SDL_WINDOW_OPENGL); // create window

	if (_window == nullptr) //check for window creation failure
	{
		returnError("window failed to create");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window); //create opengl context

	if (glContext == nullptr) //checks for context creation failure
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit(); //generate opengl enum glew initialisation

	if (error != GLEW_OK) //check for glew initialization failure
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //only draw faces facing the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //clears color
}

void Display::ClearDisplay()
{
	glClearDepth(1.0); //clears depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Display::ClearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a); //clears specific color values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

float Display::GetWidth()
{
	return _screenWidth;
}

float Display::GetHeight()
{
	return _screenHeight;
}
