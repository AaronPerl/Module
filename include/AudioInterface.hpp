#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "Sound.hpp"
#include "SoundClip.hpp"
#include "Book.hpp"
#include "ThreadObject.hpp"

namespace Module
{
	
class Sound;
class SoundClip;
class ModuleGame;

// The AudioInterface is one of Module's four core interfaces,
// and handles its titular audio. It may be used to load and
// or play sounds.
class AudioInterface : ThreadObject
{
	friend class ModuleGame;
	
	protected:
		// REPRESENTATION
		ModuleGame* game;
		Book<Sound> sounds;		// The collection of all playing sounds
		Book<SoundClip> clips;	// The collection of all loaded sounds
		void start(){};
		void run(){}; 			// Overrides ThreadObject::run()
		
	public:
		// CONSTRUCTOR
		AudioInterface(){}
		
		// FUNCTIONS
		Sound* playSound(SoundClip* clip);												// Plays a Sound
		SoundClip* loadSoundClip(const std::string& name, const std::string& fileName);	// Loads SoundClip
		void unloadSoundData(SoundClip* clip);											// Unloads SoundClip
		
		// DEBUG FUNCTIONS
		void printSounds();		// A function for debugging the sound collection
		
		// CONSTRUCTOR (Temporary, before this becomes pure virtual)
};

}

#endif
