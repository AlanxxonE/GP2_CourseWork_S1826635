#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"

class Shader
{

public:

	Shader(const std::string& filename);

	void Bind(); //set gpu to use our shaders

	void Update(const Transform& transform); //update shader class to run transform math

	std::string LoadShader(const std::string& fileName);

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint CreateShader(const std::string& text, unsigned int type);

	~Shader();

protected:

private:

	static const unsigned int NUM_SHADERS = 2; //number of shaders

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	void operator=(const Shader& other) {}
	GLuint program; //track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //number of uniform variables
};


