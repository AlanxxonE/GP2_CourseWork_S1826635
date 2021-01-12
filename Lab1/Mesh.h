#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
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

struct Sphere
{
public:

	Sphere(){}

	Sphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
		this->radius = radius;
	}

	glm::vec3 GetPos()
	{ 
		return pos; 
	}
	
	float GetRad() 
	{ 
		return radius; 
	}

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRad(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;

};

class Mesh
{

public:

	//previous mesh constructor
	Mesh(Vertex* vertices, unsigned int numVertices);

	Mesh();
	~Mesh();
	void Draw();

	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); //initialise new mesh
	void loadModel(const std::string& filename); //load 3d object from file
	void initModel(const IndexedModel& model); //draw the loaded model based on vertices sequentially based on order

	void UpdateSphereData(glm::vec3 pos, float radius);

	glm::vec3 GetSpherePos() 
	{ 
		return meshSphere.GetPos(); 
	}

	float GetSphereRad() 
	{ 
		return meshSphere.GetRad(); 
	}

	//methods that sets the position and radius of the initialised 3D model sphere collider
	void SetSpherePos(glm::vec3 pos)
	{
		meshSphere.SetPos(pos);
	}

	void SetSphereRad(float rad)
	{
		meshSphere.SetRad(rad);
	}

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshSphere; //variable struct of type sphere
	GLuint vertexArrayObject; //create array object
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject needs to be drawn
};


