#include "AudioInterface.hpp"
#include "ModuleGame.hpp"

using namespace Module;

void AudioInterface::start()
{
	game->startThread(this);
}
void AudioInterface::run()
{
	setDevice();
	setListener(NULL);
}
Sound* AudioInterface::playSound(SoundClip* clip)
{
	if(clip)
	{
		std::cout << "[AudioInterface] Playing sound from data named : " << clip->getName() << std::endl;
		sounds.push_back(Sound(clip,this));
		sounds.back().replay();
	}
	else
	{
		std::cerr << "[AudioInterface] This SoundClip is NULL!" << std::endl;
	}
	return &sounds.back();
}
SoundClip* AudioInterface::loadSoundClip(const std::string& name, const std::string& fileName)
{
	for(unsigned int i = 0; i < clips.size(); i++)
	{
		if(clips[i].getName() == name)
		{
			std::cerr << "[AudioInterface] The name \"" << name << "\" has already been used." << std::endl;
			return NULL;
		}
	}
	clips.push_back(SoundClip(name,this));
	return &clips.back();
}
void AudioInterface::debugAudio()
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
