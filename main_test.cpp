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
	Module::GameObject* camera = game.createGameObject();
	
	// camera->setPosition(Module::Vector3(0,1.732f,3));
	camera->setPosition(Module::Vector3(0,15.0f, 0.0f));
	// camera->setPosition(Module::Vector3(0,0,3));
	// camera->setRotation(Module::Quaternion(Module::Vector3(1,0,0),	-3.141592f/4.0f));
	camera->setRotation(Module::Quaternion(Module::Vector3(1,0,0),	-3.141592f/2.0f));
	
	
	// GRAPHICS TESTS
	int teapots = 10000;
	
	Module::Mesh* teapot = graphics.loadMeshFromFile("teapot", "models/cube.obj", false);	
	teapot->setScale(1/1.0f);
	
	std::vector<Module::GameObject*> objects;
		
	for (unsigned int i = 0; i < teapots; i++)
	{
		float theta = 2 * 3.141592 * i / teapots;
		Module::GameObject* gameobj = game.createGameObject();
		game.setMesh(gameobj, teapot);
		// gameobj->setPosition(Module::Vector3(i * 0.5f, 0.0f, i * 0.0f));
		gameobj->setPosition(Module::Vector3(6 * std::sin(theta), 0.0f, 6 * std::cos(theta)));
		objects.push_back(gameobj);
	}
	graphics.setCamera(camera);
	
	// AUDIO TESTS
	//Module::SoundClip* boilClip = audio.loadSoundClip("boilingWater","sounds/boiling.wav");
	Module::SoundClip* musicClip = audio.loadSoundClip("chopinScherzo","sounds/chopin_scherzo.wav");
	//audio.playSound(boilClip,1.0f,0.1f);
	Module::Sound* music = audio.playSound(musicClip,1.0f,1.0f);
	audio.debugAudio();
	
	signal(SIGINT, sigterm_handler);
	
	unsigned long millisStart = game.getMilliseconds();
	bool temp = false;
	
	while (game.isRunning())
	{
		unsigned long millis = game.getMilliseconds() - millisStart;
		float baseRot = std::sin(2 * 3.1415926535 * millis / 1000.0f);
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i]->setRotation(Module::Quaternion(Module::Vector3(0,1,0), baseRot + (2 * 3.141592f * i / teapots)));
		}
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
