#pragma once
#include <string>
#include <GL\glew.h>

//This class is used to load a texture from a file and bind it

class Texture
{

public:
	Texture(const std::string& fileName);
	void Bind(unsigned int unit); // bind up to 32 textures
	~Texture();

protected:

private:
	GLuint textureHandler;

};

