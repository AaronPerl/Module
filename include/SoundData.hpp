#ifndef __MODULE__SOUNDDATA_HPP__
#define __MODULE__SOUNDDATA_HPP__

#include <string>

namespace Module
{
class AudioInterface;
// The Sound represents a single sound's data, which
// is stored in the AudioInterface, and which is read from by
// SoundInstances, which represent the actual playing of sounds.
class SoundData
{
	friend class AudioInterface;
	
	protected:
		// REPRESENTATION
		std::string name;		// The name of this SoundData
		uint16_t numInstances;	// The number of instances (Sounds) of this SoundData
		
		// CONSTRUCTOR
		SoundData(std::string n, uint16_t* d): name(n) {}
		
	public:
		// GETTERS
		const std::string getName();		// Gets the name of this SoundData
		const uint16_t getNextUID();		// Gets the next up UID (from the number of instances)
};

}

#endif