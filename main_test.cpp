#include <cmath>
#include <iostream>
#include "ModuleGame.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include <cfloat>

#define MATH_PI 3.14159265358979323846264

float timesTwo(float x)
{
	return 2*x;
}

int main()
{
	Module::ModuleGame g;
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
	
	
	// AUDIO TESTS //
	Module::AudioInterface ai;
	Module::SoundData* sound = ai.loadSoundData("explosion",NULL);
	ai.loadSoundData("laser",NULL);
	ai.loadSoundData("murmur",NULL);
	ai.loadSoundData("music",NULL);
	ai.loadSoundData("murmur",NULL);
	ai.playSound(sound);
	ai.playSound(sound);
	ai.printSounds();
	
	return 0;
}