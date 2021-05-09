#version 120

//Define the quality bar of rendering the outcome of the shader
#ifdef GL_ES
precision highp float; //high value
#endif

//Provides a set of vectors that will store the position, the texture coordinates and the normals based on each vertex
attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normals;

//Vectors that vary based on the changes of the vertices inside the game
varying vec2 texCoord0;
varying vec3 normalsPass;

//Transform matrix affecting the 3D mesh model
uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position*5.0f, 1.0); //transform contains MVP, based on the transform matrix of the mesh
	texCoord0 = texCoord; //assign the texture coordinates
	normalsPass = normals; //pass the normals
}