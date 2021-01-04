#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

protected:

private:
	glm::vec3 pos;
	glm::vec2 texCoord; //variable that stores the position on the texture mapped to the vertex
	glm::vec3 normal;
};

class Mesh
{

public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void Draw();

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject; //create array object
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject needs to be drawn

};


