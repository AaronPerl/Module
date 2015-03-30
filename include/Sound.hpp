#ifndef __MODULE__SOUND_HPP__
#define __MODULE__SOUND_HPP__

#include <cstdio>
#include <string>
#include <stdint.h>
#include "AudioInterface.hpp"
#include "SoundData.hpp"

namespace Module
{
// A Sound represents a single playing of a sound, or,
// in some instances, the looping of that sound. It points
// to the specific SoundData being played.
class Sound
{
	friend class AudioInterface;
	
	private:
		// REPRESENTATION
		uint16_t uid;			// The UID of this Sound
		unsigned long time;		// The time of this Sound
		SoundData* soundData;	// The data this Sound is playing
		
		// CONSTRUCTOR
		Sound(SoundData* sd): uid(sd->getNextUID()), soundData(sd) {}
		
	public:
		// FUNCTIONS
		void replay();							// Plays this Sound from time 0
		void resume();							// Plays this Sound from the current time
		void pause();							// Pauses this Sound
		
		// GETTERS
		std::string getName();					// Gets the name of this Sound
		unsigned long getTime();				// Gets the time of this Sound
		
		// SETTERS
		void setTime(const unsigned long t);	// Sets the time of this Sound
		
		
};

}

#endif