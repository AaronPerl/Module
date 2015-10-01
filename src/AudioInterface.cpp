#include "AudioInterface.hpp"
#include "ModuleGame.hpp"
#include "SoundClip.hpp"
#include "Sound.hpp"

using namespace Module;

AudioInterface::AudioInterface() {} // A blank constructor

/** Starts the thread for run.
 */
void AudioInterface::start()
{
	game->startThread(this);
}
/** Overrides ThreadObject::run()
*/
void AudioInterface::run()
{
	setDevice();
	setListener(NULL);
}
/** Sets the frequency of a SoundClip.
 * @param soundClip A pointer to the SoundClip.
 * @param frequency The frequency of the clip, in Hertz.
*/
void AudioInterface::setFrequency(SoundClip* soundClip, unsigned int frequency)
{
	soundClip->setFrequency(frequency);
}
/** Plays a Sound.
 * @param clip A pointer to the SoundClip that the Sound will be of.
 * @return A pointer to the Sound, which is currently playing.
*/
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
/** Loads a SoundClip into memory.
 * @param name The name of the SoundClip, ie: "explosion."
 * @param fileName The name of the file to be loaded from.
 * @return A pointer to the loaded SoundClip.
*/
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
/** A debug method, which prints out information about the current state of game audio.
*/
void AudioInterface::debugAudio()
{
	#ifdef DEBUG
	std::cout << "[AudioInterface] SoundClips (" << sounds.size() << "):" << std::endl;
	for(unsigned int i = 0; i < clips.size(); ++i)
	{
		std::cout << "                 |" << i+1 << "| " << clips[i].getName() << std::endl;
	}
	std::cout << "                 Sounds (" << sounds.size() << "):" << std::endl;
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		std::cout << "                 |" << i+1 << "| " << sounds[i].getName() << std::endl;
	}
	#endif
}
