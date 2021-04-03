#pragma once
#pragma region unifrom setters

#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"
#include <iostream>

class Shader
{

public:

	Shader();
	
	void init(const std::string& filenameVert, const std::string& filenameFrag);

	void initGeo();

	void Bind(); //set gpu to use our shaders

	void Update(const Transform& transform); //update shader class to run transform math
	void Update(const Transform& transform, const Camera& camera); //update shader class with camera functionality

	std::string LoadShader(const std::string& fileName); //load shader from file

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); //check shader implementation errors

	GLuint CreateShader(const std::string& text, unsigned int type); //methods that instantiates the shader

	~Shader();

	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), value);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(program, name.c_str()), value);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}

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
	GLuint geoShaders[3];
	GLuint uniforms[NUM_UNIFORMS]; //number of uniform variables
};


