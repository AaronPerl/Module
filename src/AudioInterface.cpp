#include "AudioInterface.hpp"

Module::Sound* Module::AudioInterface::playSound(SoundData* soundData)
{
	if(soundData)
	{
		sounds.add(Sound(soundData));
		sounds.back().replay();
	}
	else
	{
		std::cerr << "AudioInterface: This SoundData is NULL!" << std::endl;
	}
	return &sounds.back();
}
Module::SoundData* Module::AudioInterface::loadSoundData(std::string name)
{
	for(unsigned int i = 0; i < soundData.size(); i++)
	{
		if(soundData[i].getName() == name)
		{
			std::cerr << "AudioInterface: The name \"" << name << "\" has already been used." << std::endl;
			return NULL;
		}
	}
	soundData.add(SoundData(name,data));
	return &soundData.back();
}
//TODO: Link this up in such a way that unloading SoundData removes all Sounds pointing to it.
/*
void Module::AudioInterface::unloadSoundData(Module::SoundData* sD)
{
	for(unsigned int i = 0; i < soundData.size(); i++)
	{
		if(soundData[i] == sD)
		{
			std::cerr << "AudioInterface: The name \"" << sD->getName() << "\" has already been used." << std::endl;
			soundData.erase(soundData.begin()+i);
			return;
		}
	}
}
*/
void Module::AudioInterface::printSounds()
{
	std::cout << "Sound Collection:" << std::endl;
	std::cout << " There are " << soundData.size() << "." << std::endl;
	for(unsigned int i = 0; i < soundData.size(); ++i)
	{
		std::cout << " " << i << ") " << soundData[i].getName() << std::endl;
	}
	std::cout << "Currently-playing Sounds:" << std::endl;
	std::cout << " There are " << sounds.size() << "." << std::endl;
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		std::cout << " " << i << ") " << sounds[i].getName() << std::endl;
	}
}