#pragma once
#include <string>
#include <GL\glew.h>

//This class is used to load a texture from a file and bind it

class Texture
{

public:
	Texture();

	void init(const std::string& fileName); //initialise texture
	void Bind(unsigned int unit); // bind up to 32 textures
	~Texture();

protected:

private:
	GLuint textureHandler;

};

