#include "AudioInterface.hpp"
#include "ModuleGame.hpp"

using namespace Module;

// Starts the thread for run.
void AudioInterface::start()
{
	game->startThread(this);
}
// Overrides ThreadObject::run()
void AudioInterface::run()
{
	setDevice();
	setListener(NULL);
}
// Sets the frequency
void AudioInterface::setFrequency(SoundClip* soundClip, unsigned int frequency)
{
	soundClip->setFrequency(frequency);
}
// Plays a Sound
Sound* AudioInterface::playSound(SoundClip* clip)
{
	if(clip)
	{
		#ifdef DEBUG
		std::cerr << "[AudioInterface] Now playing the Sound: " << clip->getName() << std::endl;
		#endif
		sounds.push_back(Sound(clip,this));
	}
	else
	{
		#ifdef DEBUG
		std::cerr << "[AudioInterface] This SoundClip is NULL!" << std::endl;
		#endif
	}	return &sounds.back();
}
SoundClip* AudioInterface::loadSoundClip(const std::string& name, const std::string& fileName)
{
	for(unsigned int i = 0; i < clips.size(); i++)
	{
		if(clips[i].getName() == name)
		{
			#ifdef DEBUG
			std::cerr << "[AudioInterface] The name \"" << name << "\" has already been used." << std::endl;
			#endif
			return NULL;
		}
	}
	clips.push_back(SoundClip(name,this));
	return &clips.back();
}
void AudioInterface::debugAudio()
{
	#ifdef DEBUG
	std::cout << "[AudioInterface] Sound Collection (" << sounds.size() << "):" << std::endl;
	for(unsigned int i = 0; i < clips.size(); ++i)
	{
		std::cout << "                  " << i+1 << ") " << clips[i].getName() << std::endl;
	}
	std::cout << "                 Currently-playing Sounds (" << sounds.size() << "):" << std::endl;
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		std::cout << "                  " << i+1 << ") " << sounds[i].getName() << std::endl;
	}
	#endif
}
