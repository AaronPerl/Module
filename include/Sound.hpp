#ifndef __MODULE__SOUND_HPP__
#define __MODULE__SOUND_HPP__

// C++ standard library includes
#include <cstdio>
#include <string>
#include <stdint.h>

// Module includes
#include "AudioInterface.hpp"
#include "SoundClip.hpp"
#include "Book.hpp"

namespace Module
{
// A Sound represents a single playing of a sound, or,
// in some instances, the looping of that sound. It points
// to the specific SoundClip being played.
class Sound
{
	friend class AudioInterface;
	friend class Book<Sound>;
	
	private:
		// REPRESENTATION
		uint16_t uid;			// The UID of this Sound
		unsigned long time;		// The time of this Sound
		SoundClip* soundClip;	// The data this Sound is playing
		AudioInterface* audio;	// The audioInterface that created this Sound
		
		// CONSTRUCTOR
		Sound(SoundClip* sd, AudioInterface* aI): uid(sd->getNextUID()), time(0), soundClip(sd), audio(aI) {}
		Sound(): uid(0), time(0), soundClip(NULL), audio(NULL) {}
		
	public:
		// FUNCTIONS
		void replay();		// Plays this Sound from time 0
		void resume();		// Plays this Sound from the current time
		void pause();		// Pauses this Sound
		void stop();		// Stops this Sound
		
		// GETTERS
		const std::string getName() const;		// Gets the name of this Sound
		unsigned long getTime() const;			// Gets the time of this Sound
		SoundClip* getSoundClip() const;		// Gets the SoundClip of this Sound
		
		// SETTERS
		void setTime(const unsigned long t);	// Sets the time of this Sound
		
		
};

}

#endif
