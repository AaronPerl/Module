#include <cmath>
#include <cfloat>
#include <csignal>
#include <iostream>
#include "ModuleGame.hpp"
#include "Sound.hpp"
#include "SoundClip.hpp"
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

int main(int argc, char ** argv)
{
	Module::ModuleGame game;
	Module::SDLOpenGLInterface graphics;
	Module::OpenALInterface audio;
	Module::PthreadsInterface threads;
	game.attachThreadingInterface(&threads);
	game.attachGraphicsInterface(&graphics);
	game.attachAudioInterface(&audio);
	game.start();
	
	// GRAPHICS TESTS
	// : (
	
	// AUDIO TESTS
	// : )
	//Module::SoundClip* clip = audio.loadSoundClip("ASDF","ASDF");
	//audio.playSound(clip);
	
	signal(SIGINT, sigterm_handler);
	
	while (game.isRunning());
	
	return 0;
}
