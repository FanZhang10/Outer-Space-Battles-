#include <iostream>
#include <exception>
#include "OgreApplication.h"
#include "ResourceFactory.h"

/* Macro for printing exceptions */
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

/* Main function that builds and runs the application */
int main(void){
    AsteroidGame::OgreApplication application;

	try {
		application.Init();
		application.MainLoop();
	}
	catch (std::exception &e){
		PrintException(e);
	}

    return 0;
}
