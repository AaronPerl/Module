#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "Sound.hpp"
#include "SoundClip.hpp"
#include "Book.hpp"

namespace Module
{
class Sound;
class SoundClip;
// The AudioInterface is one of Module's four core interfaces,
// and handles its titular audio. It may be used to load and
// or play sounds.
class AudioInterface
{
	public: //protected:
		// REPRESENTATION
		Book<Sound> sounds;		// The collection of all playing sounds
		Book<SoundClip> clips;	// The collection of all loaded sounds
		
	public:
		// FUNCTIONS
		Module::Sound* playSound(SoundClip*);			// Plays a Sound
		SoundClip* loadSoundClip(const std::string&);	// Loads SoundClip
		//void unloadSoundData(SoundClip*);				// Unloads SoundClip
		
		// DEBUG FUNCTIONS
		void printSounds();		// A function for debugging the sound collection
		
		// CONSTRUCTOR (Temporary, before this becomes pure virtual)
		AudioInterface(){}
};

}

#endif
