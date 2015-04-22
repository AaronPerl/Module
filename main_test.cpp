#include <cmath>
#include <cfloat>
#include <csignal>
#include <iostream>
#include "ModuleGame.hpp"
#include <OpenALInterface.hpp>
#include <SDLOpenGLInterface.hpp>
#include <PthreadsInterface.hpp>

#include "Vector3.hpp"
#include "Quaternion.hpp"

#define MATH_PI 3.14159265358979323846264

bool halted = false;

void sigterm_handler(int signal)
{
	if (signal == SIGINT)
	{
		halted = true;
		std::cout << "Terminated!" << std::endl;
	}
}

float timesTwo(float x)
{
	return 2*x;
}

int main(int argc, char ** argv)
{
	Module::ModuleGame g;
	Module::SDLOpenGLInterface graphics;
	Module::OpenALInterface audio;
	Module::PthreadsInterface threads;
	g.attachThreadingInterface(&threads);
	g.attachGraphicsInterface(&graphics);
	g.attachAudioInterface(&audio);
	g.start();
	
	// GRAPHICS TESTS
	// : (
	
	// AUDIO TESTS
	// : )
	
	
	signal(SIGINT, sigterm_handler);
	
	while (g.isRunning());
	
	return 0;
}
