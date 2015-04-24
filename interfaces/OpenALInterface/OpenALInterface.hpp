#ifndef __MODULE__OPENALINTERFACE_HPP__
#define __MODULE__OPENALINTERFACE_HPP__

// C++ standard library includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

// Module includes
#include <ModuleGame.hpp>
#include <AudioInterface.hpp>
#include <Book.hpp>

// Library includes
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

namespace Module
{
	// The OpenAL implementation of the AudioInterface
	class OpenALInterface : public AudioInterface
	{
		protected:
			// REPRESENTATION
			Book<ALuint> soundNames;	// The "names" of all playing sounds
			Book<ALuint> clipNames;		// The "names" of all loaded sounds
			Book<uint16_t> pcmData;		// The underlying PCM data
			
			ALCdevice* device;
			ALCcontext* context;
			
			void replaySound(Sound*) {};	// Replays a Sound
			void resumeSound(Sound*) {};	// Resumes a Sound
			void pauseSound(Sound*) {};		// Pauses a Sound
			void stopSound(Sound*) {};		// Stops a Sound
			void setDevice();
			void setListener(GameObject*);
			
		public:
			OpenALInterface();
			Sound* playSound(SoundClip*);					// Plays a Sound
			Sound* playSound(SoundClip*, float, float);		// Plays a Sound
			SoundClip* loadSoundClip(const std::string&, 
									 const std::string&);	// Loads SoundClip
			void unloadSoundClip(SoundClip*);				// Unloads SoundClip	
	};

}

#endif
