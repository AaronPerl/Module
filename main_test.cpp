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
	Module::PthreadsInterface threads;
	g.attachThreadingInterface(&threads);
	g.attachGraphicsInterface(&graphics);
	g.start();
	// UTILITY TESTS //
	Module::Vector3 vec(0,10,0);
	
	/*Module::Quaternion quat1(3,4,3,0);
	Module::Quaternion quat2(3.9,-1,-3,4);
	Module::Quaternion quat3 = quat1 * quat2;
	std::cout << quat3.getX() << "," << quat3.getY() << "," << quat3.getZ() << "," << quat3.getW() << std::endl;
	Module::Quaternion quat4 = quat1.pow(3.4);
	std::cout << quat4.getX() << "," << quat4.getY() << "," << quat4.getZ() << "," << quat4.getW() << std::endl;
	std::cout << vec.getY() << std::endl;
	std::cout << 1-FLT_EPSILON << std::endl;*/
	/*Module::Quaternion quat1(Module::Vector3(0,1,0),0);
	Module::Quaternion quat2(Module::Vector3(1,0,0),MATH_PI/2);
	std::cout << quat1 << std::endl;
	std::cout << Module::slerp(quat1,quat2,0.5f) << std::endl;
	std::cout << quat2 << std::endl;*/
	//std::cout << quat1 << std::endl;
	
	Module::Quaternion rot(Module::Vector3(1,0,0),MATH_PI/2);
	std::cout << rot << std::endl;
	std::cout << vec.rotate(rot) << std::endl;
	/*
	Module::DynamicArray<unsigned int> testArray;
	std::cout << "Initial size = " << testArray.capacity() << std::endl;
	for (unsigned int i = 0; i < 257; i++)
	{
		testArray.add(i);
	}
	std::cout << "Size after 257 additions = " << testArray.capacity() << std::endl;
	*/
	// GRAPHICS TESTS //
	// :( //
	
	// AUDIO TESTS //
	/*
	Module::AudioInterface ai;
	std::cout << ai.soundData.size() << " Start size = " << ai.soundData.capacity() << std::endl;
	Module::SoundData* sound = ai.loadSoundData("explosion");
	std::cout << ai.soundData.size() << " End size = " << ai.soundData.capacity() << std::endl;
	std::cout << " Name = " << sound->getName() << std::endl;
	ai.loadSoundData("laser");
	ai.loadSoundData("murmur");
	ai.loadSoundData("music");
	ai.loadSoundData("murmur");
	ai.playSound(sound);
	ai.playSound(sound);
	ai.printSounds();
	*/
	
	signal(SIGINT, sigterm_handler);
	
	while (g.isRunning());
	
	return 0;
}
