#include "OpenALInterface.hpp"

void Module::OpenALInterface::start()
{
	// Open device handle
	device = alcOpenDevice(NULL); // Open the default device
	if (!device)
	{
		std::cerr << "AudioInterface: Error opening device!" << std::endl;
	}
	std::cout << "AudioInterface: Opened a device successfully." << std::endl;
	// Initialize the context
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		std::cerr << "AudioInterface: Could not make context current" << std::endl;
	}
	std::cout << "AudioInterface: Created a context successfully." << std::endl;
}
void Module::OpenALInterface::run()
{
	
}
Module::Sound* Module::OpenALInterface::playSound(SoundClip* clip)
{
	return NULL;
}
Module::SoundClip* Module::OpenALInterface::loadSoundClip(const std::string& name, const std::string& fileName)
{
	return NULL;	
}
void Module::OpenALInterface::unloadSoundData(SoundClip* clip)
{
	
}