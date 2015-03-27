#include "Sound.hpp"

void Module::Sound::replay()
{
	// Replaying code
}
void Module::Sound::resume()
{
	// Replaying code
}
void Module::Sound::pause()
{
	// Pause code
}
void Module::Sound::setTime(const unsigned long t)
{
	// Set time code
	time = t;
}
std::string Module::Sound::getName()
{
	char name[20];
	sprintf(name,"%u", uid);
	std::string s(name);
	return soundData->getName() + "_" + s;
}
unsigned long Module::Sound::getTime()
{
	// Get time code
	return time;
}