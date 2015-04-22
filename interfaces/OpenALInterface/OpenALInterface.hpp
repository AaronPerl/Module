#ifndef __MODULE__OPENALINTERFACE_HPP__
#define __MODULE__OPENALINTERFACE_HPP__

// C++ standard library includes
#include <iostream>
#include <string>
#include <vector>

// Module includes
#include <ModuleGame.hpp>
#include <AudioInterface.hpp>
#include <Book.hpp>

// Library includes
#include <AL/al.h>
#include <AL/alc.h>

namespace Module
{
	// The OpenAL implementation of the AudioInterface
	class OpenALInterface : public AudioInterface
	{
		protected:
			// REPRESENTATION
			Book<ALuint> soundNames;	// The "names" of all playing sounds
			Book<ALuint> clipNames;		// The "names" of all loaded sounds
			
			ALCdevice* device;
			ALCcontext* context;
			
			void start();
			void run();
			
		public:
			OpenALInterface() {};
			Sound* playSound(SoundClip* clip);												// Plays a Sound
			SoundClip* loadSoundClip(const std::string& name, const std::string& fileName);	// Loads SoundClip
			void unloadSoundData(SoundClip* clip);											// Unloads SoundClip
	};

}

#endif
