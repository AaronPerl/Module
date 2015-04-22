#ifndef __MODULE__SOUNDCLIP__HPP__
#define __MODULE__SOUNDCLIP__HPP__

// C++ standard library includes
#include <string>
#include <stdint.h>
#include <vector>

// Module includes
#include "Book.hpp"

namespace Module
{
class AudioInterface;
// The SoundClip represents a single sound's data, which
// is stored in the AudioInterface, and which is read from by
// SoundInstances, which represent the actual playing of sounds.
class SoundClip
{
	friend class AudioInterface;
	friend class Book<SoundClip>;
	
	protected:
		// REPRESENTATION
		std::string name;		// The name of this SoundClip
		uint16_t numInstances;	// The number of instances (Sounds) of this SoundClip
		AudioInterface* audio;	// The audioInterface that created this Sound
		
		// CONSTRUCTOR
		SoundClip(std::string n, AudioInterface* aI): name(n), numInstances(0), audio(aI) {}
		SoundClip(): name("DEFAULT"), numInstances(0), audio(NULL) {}
	public:
		// GETTERS
		const std::string& getName() const;	// Gets the name of this SoundClip
		uint16_t getNextUID();				// Gets the next up UID (from the number of instances)
};

}

#endif
