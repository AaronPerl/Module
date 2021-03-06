#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

// C++ standard library includes
#include <iostream>

#include <EASTL/string.h>
#include <EASTL/vector.h>

// Module includes
#include "ModuleDefines.hpp"
#include "ThreadObject.hpp"
#include "Book.hpp"

namespace Module
{
/** The AudioInterface is one of Module's four core interfaces,
 * and handles its titular audio. It may be used to load and
 * or play sounds.
 */
class AudioInterface : ThreadObject
{
	// This is a very amiable interface
	friend class Sound;
	friend class SoundClip;
	friend class ModuleGame;
	
	protected:
		// REPRESENTATION
		ModuleGame* game;			/**< The game that this is a part of */
		GameObject* listener;		/**< The listener GameObject */
		Book<Sound> sounds;			/**< The collection of all playing sounds */
		Book<SoundClip> clips;		/**< The collection of all loaded sounds */
		
		// FUNCTIONS
		void start();				/**< Starts the thread for run. */
		void run(); 				/**< Overrides ThreadObject::run() */
		
		// IMPLEMENT THIS
		virtual void updateEnvironment() = 0; 	/**< Updates positions, velocities, etc. */
		
		// IMPLEMENT FOR GAMEOBJECT & MODULEGAME
		virtual Sound* playSound(SoundClip*, GameObject*);			// Plays a Sound
		virtual SoundClip* loadSoundClip(const eastl::string&, 
										 const eastl::string&);		// Loads SoundClip
		virtual void unloadSoundClip(SoundClip*) = 0;				// Unloads SoundClip
		
		// IMPLEMENT THESE FOR SOUND
		virtual void replaySound(Sound*) = 0;		// Replays a Sound
		virtual void resumeSound(Sound*) = 0;		// Resumes a Sound
		virtual void pauseSound(Sound*) = 0;		// Pauses a Sound
		virtual void stopSound(Sound*) = 0;			// Stops a Sound
		virtual void setDevice() = 0;				// Sets the device
		virtual void setListener(GameObject*) = 0;	// Sets the listener GameObject
		
		// IMPLEMENT THESE FOR SOUNDCLIPS
		virtual void setFrequency(SoundClip*, unsigned int);	// Sets the frequency
			
		// DEBUG FUNCTIONS
		void debugAudio();	// A function for debugging the sound collection
		
	public:
		// CONSTRUCTOR
		AudioInterface();	// A blank constructor
};

}

#endif
