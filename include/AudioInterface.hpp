#ifndef __MODULE__AUDIOINTERFACE_HPP__
#define __MODULE__AUDIOINTERFACE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "Sound.hpp"
#include "SoundData.hpp"
#include "DynamicArray.hpp"

namespace Module
{
class Sound;
class SoundData;
// The AudioInterface is one of Module's four core interfaces,
// and handles its titular audio. It may be used to load and
// or play sounds.
class AudioInterface
{
	public: //protected:
		// REPRESENTATION
		DynamicArray<Sound> sounds;				// The collection of all playing sounds
		DynamicArray<SoundData> soundData;		// The collection of all loaded sounds
		
	public:
		// FUNCTIONS
		Module::Sound* playSound(SoundData*);				// Plays a Sound
		SoundData* loadSoundData(std::string);				// Loads SoundData
		//void unloadSoundData(SoundData*);					// Unloads SoundData
		
		// DEBUG FUNCTIONS
		void printSounds();		// A function for debugging the sound collection
		
		// CONSTRUCTOR (Temporary, before this becomes pure virtual)
		AudioInterface(){}
};

}

#endif