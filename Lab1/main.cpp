#include <iostream>
#include "MainGame.h"

int main(int argc, char** argv) //argument used to call SDL main
{
	MainGame mainGame; //creates a MainGame Instance
	mainGame.run(); //executes the run method

	return 0;
}