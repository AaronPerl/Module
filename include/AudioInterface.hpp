#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

// C++ standard library includes
#include <iostream>
#include <string>
#include <vector>

// Module includes
#include "Sound.hpp"
#include "SoundClip.hpp"
#include "Book.hpp"
#include "ThreadObject.hpp"
#include "GameObject.hpp"

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
	// This is a very amiable interface
	friend class Sound;
	friend class SoundClip;
	friend class ModuleGame;
	
	protected:
		// REPRESENTATION
		ModuleGame* game;		// The game that this is a part of
		GameObject* listener;	// The listener GameObject
		Book<Sound> sounds;		// The collection of all playing sounds
		Book<SoundClip> clips;	// The collection of all loaded sounds
		
		// FUNCTIONS
		void start();	// Starts the thread for run.
		void run(); 	// Overrides ThreadObject::run()
		
		// IMPLEMENT THESE FOR SOUND
		virtual void replaySound(Sound*) = 0;		// Replays a Sound
		virtual void resumeSound(Sound*) = 0;		// Resumes a Sound
		virtual void pauseSound(Sound*) = 0;		// Pauses a Sound
		virtual void stopSound(Sound*) = 0;			// Stops a Sound
		virtual void setDevice() = 0;				// Sets the device
		virtual void setListener(GameObject*) = 0;	// Sets the listener object
		
		// IMPLEMENT THESE FOR SOUNDCLIPS
		virtual void setFrequency(SoundClip*, unsigned int);	// Sets the frequency
		
	public:
		// CONSTRUCTOR
		AudioInterface(){}	// Necessary evil
		
		// DEBUG FUNCTIONS
		void debugAudio();	// A function for debugging the sound collection
		
		// IMPLEMENT THESE
		virtual Sound* playSound(SoundClip*);						// Plays a Sound
		virtual Sound* playSound(SoundClip*, float, float) = 0;		// Plays a Sound
		virtual SoundClip* loadSoundClip(const std::string&, 
										 const std::string&);		// Loads SoundClip
		virtual void unloadSoundClip(SoundClip*) = 0;				// Unloads SoundClip		
};

}

#endif
