#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Audio
{
	struct data 
	{
		int sourceID, bufferID;

		char* buffer;

		std::string name;

		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};

	std::vector<data> datas;

	ALCcontext* context;

	ALCdevice *device;

	bool isBigEndian(); //method that finds out if the computer is using Big or Little Endian in order to read the sound data properly

	int convertToInt(char* buffer, int length); //converts a char array into int array

	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size); //method that reads a WAV file allowing openAL to play the sound back

public:

	Audio();
	~Audio();

	unsigned int loadSound(const char* filename); //takes a file from a pathway and load it while also figuring the type of audio out
	void deleteSound(unsigned int id); //deletes a sound based on a specific ID
	void playSound(unsigned int id); //plays a sound based on a specific ID
	void playSound(unsigned int id, glm::vec3& pos); //Plays a sound by calling the int handler and the 3D position the sound needs to be reproduced 
	void stopSound(unsigned int id); //stops a sound based on a specific ID

	void setlistener(glm::vec3& pos, glm::vec3& camLookAt); //sets the position of the listener and where the listener is looking

private:
	
};

