#ifndef __MODULE__SOUNDCLIP__HPP__
#define __MODULE__SOUNDCLIP__HPP__

#include <string>
#include <stdint.h>
#include <vector>
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
		
		// CONSTRUCTOR
		SoundClip(std::string n, std::vector<uint16_t> d): name(n), numInstances(0) {}
		SoundClip() : name(""), numInstances(0) {}
	public:
		// GETTERS
		const std::string& getName() const;	// Gets the name of this SoundClip
		uint16_t getNextUID();				// Gets the next up UID (from the number of instances)
};

}

#endif
