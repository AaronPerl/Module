#ifndef __MODULE__SOUNDDATA_HPP__
#define __MODULE__SOUNDDATA_HPP__

#include <string>
#include <stdint.h>
#include <vector>
#include "Book.hpp"

namespace Module
{
class AudioInterface;
// The Sound represents a single sound's data, which
// is stored in the AudioInterface, and which is read from by
// SoundInstances, which represent the actual playing of sounds.
class SoundData
{
	friend class AudioInterface;
	friend class Book<SoundData>;
	
	protected:
		// REPRESENTATION
		std::string name;		// The name of this SoundData
		uint16_t numInstances;	// The number of instances (Sounds) of this SoundData
		
		// CONSTRUCTOR
		SoundData(std::string n, std::vector<uint16_t> d): name(n), numInstances(0) {}
		SoundData() : name(""), numInstances(0) {}
	public:
		// GETTERS
		const std::string& getName() const;	// Gets the name of this SoundData
		uint16_t getNextUID();				// Gets the next up UID (from the number of instances)
};

}

#endif
