/////////////////////////
//GLOBAL VARIABLE LOADING
/////////////////////////

/*
	Instructions for adding new debug values:
	1) Add your new runtime value into GlobalVariableValues.txt (Follow examples in file)
		- The reader ignores everything except what's in between tildes, so anything in the file
		  not contained between tildes can be considered comments/for information purposes
	2) Add new global variable in the "GLOBAL FLOATS" section below
		- We can only easily get float values, so 1.0f/0.0f == TRUE/FALSE for boolean usage
		- I name these vars similarly to define notations: All caps, starting with GL_ for global
	3) Add new getNextFloat assignment statement in "setAllGlobalVars()"
		- It should match the other assignment statements
*/
#ifndef GLOB_VAR_LOADING_H
#define GLOB_VAR_LOADING_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TILDE 126
#define TILDECHAR '~'

///////////////
//GLOBAL FLOATS
///////////////
float GL_ASTEROID_NUM; //Number of starting asteroids


// Helper function; Reads txt stream and returns value after next TILDE, aka '~', character
// Note: ON and OFF are valid inputs; These are parsed as 1.0f and 0.0f respectively
float getNextFloat(ifstream& in)
{
	string readline;
	in.ignore(256, TILDE); 
	getline(in, readline, TILDECHAR);

	if (readline == "OFF")
		return 0.0f;
	else if (readline == "ON")
		return 1.0f;
	else
		return stof(readline);
}

// Main var setting function
// Add your new gloval var assignment below using getNextFloat
void setAllGlobalVars()
{
	ifstream varValueFile("GlobalVariableValues.txt");
	if (varValueFile.is_open())
	{
		GL_ASTEROID_NUM = getNextFloat(varValueFile);

		/*	Example assignments:
			GL_TEST_BOOLEAN = getNextFloat(varValueFile);
			GL_PLAYER_SPEED = getNextFloat(varValueFile);
		*/
	}
}


#endif