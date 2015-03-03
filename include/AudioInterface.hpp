#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

#include <iostream>
#include <string>
#include "SoundObject.hpp"
#include "SoundInstance.hpp"

namespace Module
{
	class AudioInterface
	{
		protected:
			unsigned int numSounds;				// The number of SoundObjects
			unsigned int numPlaying;			// The number of currently-playing SoundObjects
			
			SoundObject*	soundObjects[5];	// The collection of all sounds
			SoundInstance*	soundInstances[5];	// The collection of all currently-playing sounds
		
		public:
			// FUNCTIONS
			SoundObject* createSound(std::string, uint16_t*);	// Assembles a SoundObject (returns success)
			bool removeSound(SoundObject*);						// Removes a SoundObject by its pointer (returns success)
			bool removeSound(std::string);						// Removes a SoundObject by its name (returns success)
			bool playSound(SoundObject*);						// Creates a SoundInstance by its pointer (returns success)
			bool playSound(std::string);						// Creates a SoundInstance by its name (returns success)
			
			// DEBUG FUNCTIONS
			void printSoundObjects();					// A function for debugging the sound collection
			void printSoundInstances();					// A function for debugging the currently-playing sounds
			
			// CONSTRUCTOR (Temporary, before this becomes pure virtual)
			AudioInterface():	numSounds((unsigned int)0),
								numPlaying((unsigned int)0){}
	};
}

#endif