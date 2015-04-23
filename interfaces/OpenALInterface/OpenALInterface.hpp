#ifndef __MODULE__OPENALINTERFACE_HPP__
#define __MODULE__OPENALINTERFACE_HPP__

// C++ standard library includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Module includes
#include <ModuleGame.hpp>
#include <AudioInterface.hpp>
#include <Book.hpp>

// Library includes
#include <AL/al.h>
#include <AL/alc.h>
//#include <alut.h>

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
			
			void replaySound(Sound*) {};	// Replays a Sound
			void resumeSound(Sound*) {};	// Resumes a Sound
			void pauseSound(Sound*) {};		// Pauses a Sound
			void stopSound(Sound*) {};		// Stops a Sound
			void setDevice();
			void setListener(GameObject*);
			
		public:
			OpenALInterface() {};
			Sound* playSound(SoundClip* clip);												// Plays a Sound
			SoundClip* loadSoundClip(const std::string& name, const std::string& fileName);	// Loads SoundClip
			void unloadSoundClip(SoundClip* clip);											// Unloads SoundClip
	};

}

#endif
