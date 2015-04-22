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
class GameObject;
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
		GameObject* listener;
		Book<Sound> sounds;		// The collection of all playing sounds
		Book<SoundClip> clips;	// The collection of all loaded sounds
		
		void start();			// Called by run()
		void run(); 			// Overrides ThreadObject::run()
		
		virtual void setDevice() = 0;
		virtual void setListener() = 0;
		virtual void setListener(GameObject*) = 0;
		
	public:
		// CONSTRUCTOR
		AudioInterface(){}
		
		// IMPLEMENT THESE
		virtual Sound* playSound(SoundClip*) = 0;										// Plays a Sound
		virtual SoundClip* loadSoundClip(const std::string&, const std::string&) = 0;	// Loads SoundClip
		virtual void unloadSoundData(SoundClip*) = 0;									// Unloads SoundClip
		
		// DEBUG FUNCTIONS
		void printSounds();		// A function for debugging the sound collection
		
};

}

#endif
