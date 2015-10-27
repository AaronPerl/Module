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
#include "Sound.hpp"
#include "SoundClip.hpp"
#include "InputCallback.hpp"

#define MATH_PI 3.14159265358979323846264

// The Chopin comes from https://archive.org/details/onclassical-quality-wav-audio-files-of-classical-music

class TestInputCallback : public Module::InputCallback
{
public:
	virtual void onMouseDown(uint8_t button, uint16_t x, uint16_t y)
	{
		switch (button)
		{
			case 0:
				std::cout << "Left";
				break;
			case 1:
				std::cout << "Right";
				break;
			case 2:
				std::cout << "Middle";
		}
		std::cout << " mouse button pressed at location <" << x << "," << y << ">" << std::endl;
	}
	virtual void onMouseUp(uint8_t button, uint16_t x, uint16_t y)
	{
		switch (button)
		{
			case 0:
				std::cout << "Left";
				break;
			case 1:
				std::cout << "Right";
				break;
			case 2:
				std::cout << "Middle";
		}
		std::cout << " mouse button released at location <" << x << "," << y << ">" << std::endl;
	}
	/*virtual void onMouseMove(uint16_t x, uint16_t y, int16_t dx, int16_t dy)
	{
		std::cout << "Mouse moved to location <" << x << "," << y << ">" << std::endl;
		std::cout << "Relative movement vector was <" << dx << "," << dy << ">" << std::endl;
	}*/
	virtual void onKeyDown(Module::KeyCode::Code code, char keyChar)
	{
		std::cout << "Key press: code = " << code << " char = " << keyChar << std::endl;
	}
};

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
	
	TestInputCallback input;
	graphics.addInputCallback(&input);
	
	// Starts the game
	game.start();
	
	// Create a game object
	Module::GameObject* camera = game.createGameObject();
	
	// camera->setPosition(Module::Vector3(0,1.732f,3));
	camera->setPosition(Module::Vector3(0,15.0f, 0.0f));
	// camera->setPosition(Module::Vector3(0,0,3));
	// camera->setRotation(Module::Quaternion(Module::Vector3(1,0,0),	-3.141592f/4.0f));
	camera->setRotation(Module::Quaternion(Module::Vector3(1,0,0),	-MATH_PI/2.0f));
	
	
	// GRAPHICS TESTS
	unsigned int teapots = 10;
	
	Module::Mesh* teapot = graphics.loadMeshFromFile("teapot", "models/teapot.obj", true);	
	teapot->setScale(1/60.0f);
	
	std::vector<Module::GameObject*> objects;
		
	for (unsigned int i = 0; i < teapots; i++)
	{
		float theta = 2 * MATH_PI * i / teapots;
		Module::GameObject* gameobj = game.createGameObject();
		game.setMesh(gameobj, teapot);
		// gameobj->setPosition(Module::Vector3(i * 0.5f, 0.0f, i * 0.0f));
		gameobj->setPosition(Module::Vector3(6 * std::sin(theta), 0.0f, 6 * std::cos(theta)));
		objects.push_back(gameobj);
	}
	graphics.setCamera(camera);
	
	
	
	
	
	// AUDIO TESTS
	Module::SoundClip* boilClip = game.loadSoundClip("boilingWater","sounds/boiling.wav");
	Module::SoundClip* musicClip = game.loadSoundClip("chopinScherzo","sounds/chopin_scherzo.wav");
	Module::GameObject* thing = game.createGameObject();
	thing->setPosition(Module::Vector3(0,0,0));
	thing->playSound(boilClip);
	Module::Sound* music = game.playSound(musicClip);//,1.0f,1.0f);
	game.debugAudio();
	
	
	
	
	signal(SIGINT, sigterm_handler);
	
	unsigned long millisStart = game.getMilliseconds();
	
	while (game.isRunning())
	{
		unsigned long millis = game.getMilliseconds() - millisStart;
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			thing->setPosition(Module::Vector3(5*std::sin(2 * MATH_PI * millis / 1000.0f),0,0));
			objects[i]->setRotation(Module::Quaternion(Module::Vector3(0,1,0), std::sin(2 * MATH_PI * millis / 1000.0f) + (2 * MATH_PI * i / teapots)));
		}		
	}
	// END AUDIO TESTS
	
	return 0;
}
