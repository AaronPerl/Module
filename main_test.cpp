#include <cmath>
#include <cfloat>
#include <csignal>
#include <iostream>

// Module includes
#include <ModuleGame.hpp>
#include <OpenALInterface.hpp>
#include <SDLOpenGLInterface.hpp>
#include <PthreadsInterface.hpp>
#include "Vector3.hpp"
#include "Quaternion.hpp"

#define MATH_PI 3.14159265358979323846264

// The Chopin comes from https://archive.org/details/onclassical-quality-wav-audio-files-of-classical-music

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
	// Create the game
	Module::ModuleGame game;
	
	// Create the interfaces
	Module::SDLOpenGLInterface graphics;
	Module::OpenALInterface audio;
	Module::PthreadsInterface threads;
	
	// Attatch the interfaces to the game
	game.attachThreadingInterface(&threads);
	game.attachGraphicsInterface(&graphics);
	game.attachAudioInterface(&audio);
	
	// Starts the game
	game.start();
	
	// Create a game object
	Module::GameObject* gameobj = game.createGameObject();
	Module::GameObject* camera = game.createGameObject();
	
	camera->setPosition(Module::Vector3(0,1.732f,3));
	// camera->setPosition(Module::Vector3(0,0,3));
	camera->setRotation(Module::Quaternion(Module::Vector3(1,0,0),	-3.141592f/6.0f));
	
	// GRAPHICS TESTS
	Module::Mesh* teapot = graphics.loadMeshFromFile("teapot", "models/teapot.obj", true);
	teapot->setScale(1/60.0f);
	game.setMesh(gameobj, teapot);
	graphics.setCamera(camera);
	
	
	
	
	
	// AUDIO TESTS
	Module::SoundClip* boilClip = audio.loadSoundClip("boilingWater","sounds/boiling.wav");
	Module::SoundClip* musicClip = audio.loadSoundClip("chopinScherzo","sounds/chopin_scherzo.wav");
	audio.playSound(boilClip,1.0f,0.1f);
	Module::Sound* music = audio.playSound(musicClip,1.0f,1.0f);
	audio.debugAudio();
	// END AUDIO TESTS
	
	
	
	
	
	signal(SIGINT, sigterm_handler);
	
	unsigned long millisStart = game.getMilliseconds();
	bool temp = false;
	
	while (game.isRunning())
	{
		unsigned long millis = game.getMilliseconds() - millisStart;
		gameobj->setRotation(Module::Quaternion(Module::Vector3(0,1,0), millis/1000.0f));
		
		if(temp == false && millis >= 3000 && millis < 4000)
		{
			music->pause();
			temp = true;
		}
		if(temp == true && millis >= 4000)
		{
			music->resume();
			temp = false;
		}
	}
	
	return 0;
}
