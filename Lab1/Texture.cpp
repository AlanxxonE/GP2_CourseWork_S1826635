#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int textureWidth, textureHeight, numberOfComponents; //width, height, and number of components of the image

	//method that loads the image from file, passing the addresses of the integers aforementioned to write the data
	unsigned char* imageData = stbi_load((fileName).c_str(), &textureWidth, &textureHeight, &numberOfComponents, 4); 

	if (imageData == NULL) //check the image data loaded
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler); //generate the buffer to store the texture, arguments: number of and address of textures

	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture, arguments: define type & specify texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture outside width

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification(texture is smaller than area)

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnification(texture is larger)

	//send texture to the GPU
	//parameters: Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Images Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); 

	stbi_image_free(imageData); //delete the data from CPU 
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureHandler); //delete textures, arguments: number of and address of textures
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit

	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture, arguments: type of and texture to bind to unit
}
