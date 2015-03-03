//#include "ModuleGame.hpp"
#include "AudioInterface.hpp"

Module::SoundObject* Module::AudioInterface::createSound(std::string name, uint16_t* data)
{
	for(unsigned int i = 0; i < numSounds; i++)
	{
		if(soundObjects[i]->getName() == name)
		{
			return NULL;
		}
	}
	soundObjects[numSounds++] = new SoundObject(name, data);
	return soundObjects[numSounds-1]; // What if the name's taken?
}
bool Module::AudioInterface::removeSound(SoundObject* sound)
{
	for(unsigned int i = 0; i < numSounds; i++)
	{
		if(soundObjects[i] == sound)
		{
			delete soundObjects[i];
			soundObjects[i] = NULL;
			return true;
		}
	}
	return false;
}
bool Module::AudioInterface::removeSound(std::string name)
{
	for(unsigned int i = 0; i < numSounds; i++)
	{
		if(soundObjects[i]->getName() == name)
		{
			delete soundObjects[i];
			soundObjects[i] = NULL;
			return true;
		}
	}
	return false;
}
bool Module::AudioInterface::playSound(SoundObject* sound)
{
	for(unsigned int i = 0; i < numSounds; i++)
	{
		if(soundObjects[i] == sound)
		{
			soundInstances[numPlaying++] = new SoundInstance((soundObjects[i]->numInstances++),soundObjects[i]);
		}
	}
	return false;
}
bool Module::AudioInterface::playSound(std::string name)
{
	for(unsigned int i = 0; i < numSounds; i++)
	{
		if(soundObjects[i]->getName() == name)
		{
			soundInstances[numPlaying++] = new SoundInstance((soundObjects[i]->numInstances++),soundObjects[i]);
		}
	}
	return false;
}
void Module::AudioInterface::printSoundObjects()
{
	std::cout << "Sound Collection:" << std::endl;
	std::cout << " There are " << numSounds << "." << std::endl;
	for(unsigned int i = 0; i < numSounds; i++)
	{
		std::cout << " " << i << ") " << soundObjects[i]->getName() << std::endl;
	}
}
void Module::AudioInterface::printSoundInstances()
{
	std::cout << "Currently-playing Sounds:" << std::endl;
	std::cout << " There are " << numPlaying << "." << std::endl;
	for(unsigned int i = 0; i < numPlaying; i++)
	{
		std::cout << " " << i << ") " << soundInstances[i]->getName() << std::endl;
	}
}