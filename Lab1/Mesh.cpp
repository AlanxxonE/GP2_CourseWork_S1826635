#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices; //set drawCount equals to the number of vertices passed in as an argument

	glGenVertexArrays(1, &vertexArrayObject); //generate one vertex array and set the location where it needs to store it

	glBindVertexArray(vertexArrayObject); //bind the vertex array object making it functioning

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate buffers based on the array of data

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //bind the buffer with array type of data and, pass array var so that tge buffer knows the specified positions

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
