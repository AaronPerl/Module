#include "AudioInterface.hpp"

Module::Sound* Module::AudioInterface::playSound(SoundClip* clips)
{
	if(clips)
	{
		std::cout << "Playing sound from data named : " << clips->getName() << std::endl;
		sounds.push_back(Sound(clips));
		sounds.back().replay();
	}
	else
	{
		std::cerr << "AudioInterface: This clips is NULL!" << std::endl;
	}
	return &sounds.back();
}
Module::SoundClip* Module::AudioInterface::loadclips(const std::string& name)
{
	for(unsigned int i = 0; i < clips.size(); i++)
	{
		if(clips[i].getName() == name)
		{
			std::cerr << "AudioInterface: The name \"" << name << "\" has already been used." << std::endl;
			return NULL;
		}
	}
	clips.push_back(clips(name,std::vector<uint16_t>()));
	return &clips.back();
}
//TODO: Link this up in such a way that unloading clips removes all Sounds pointing to it.
/*
void Module::AudioInterface::unloadclips(Module::SoundClip* sD)
{
	for(unsigned int i = 0; i < clips.size(); i++)
	{
		if(clips[i] == sD)
		{
			std::cerr << "AudioInterface: The name \"" << sD->getName() << "\" has already been used." << std::endl;
			clips.erase(clips.begin()+i);
			return;
		}
	}
}
*/
void Module::AudioInterface::printSounds()
{
	std::cout << "Sound Collection:" << std::endl;
	std::cout << " There are " << clips.size() << "." << std::endl;
	for(unsigned int i = 0; i < clips.size(); ++i)
	{
		std::cout << " " << i << ") " << clips[i].getName() << std::endl;
	}
	std::cout << "Currently-playing Sounds:" << std::endl;
	std::cout << " There are " << sounds.size() << "." << std::endl;
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		std::cout << " " << i << ") " << sounds[i].getName() << std::endl;
	}
}
