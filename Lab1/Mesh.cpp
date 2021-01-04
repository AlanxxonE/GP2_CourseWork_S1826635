#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices; //set drawCount equals to the number of vertices passed in as an argument

	std::vector<glm::vec3> positions; //holds the position data
	std::vector<glm::vec2> textCoords; //holds the texture coordinate data

	positions.reserve(numVertices); // reserve the space needed to hold the positions data
	textCoords.reserve(numVertices); // reserve the space needed to hold the texture coordinates data

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos()); //store the array of vertex positon into a list vec3 positions
		textCoords.push_back(*vertices[i].GetTexCoord()); //store the array of texture coordinate into a list vec2 positions
	}

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of the array of data

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //bind the buffer with array type of data and, pass array var so that the buffer knows the specified positions
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0],GL_STATIC_DRAW); //move the data to the GPU and specify the type of data, size of data, start pointer of data, and where the data on the GPU is stored

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //bind the buffer with array type of data and, pass array var so that the buffer knows the specified positions
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW); //move the data to the GPU and specify the type of data, size of data, start pointer of data, and where the data on the GPU is stored

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // unbind our VAO


	glGenVertexArrays(1, &vertexArrayObject); //generate one vertex array and set the location where it needs to store it
	glBindVertexArray(vertexArrayObject); //bind the vertex array object making it functioning
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate buffers based on the array of data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //bind the buffer with array type of data and, pass array var so that the buffer knows the specified positions
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW); //move the data to the GPU and specify the type of data, size of data, start pointer of data, and where the data on the GPU is stored
	glEnableVertexAttribArray(0); //specify to openGL the number of attributes present in our object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //arguments: what to analyze, number of pieces of data, type of data, normalise, what data needs to be skipped, distance to first attribute
	glBindVertexArray(0); //unbind the buffer
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); //delete the arrays that were generated 
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject); //bind the array

	glDrawArrays(GL_TRIANGLES, 0, drawCount); //draw the array, arguments: draw mode, start draw position, end draw position

	glBindVertexArray(0); //unbind the array
}
