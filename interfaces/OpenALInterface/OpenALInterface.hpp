#ifndef __MODULE__OPENALINTERFACE_HPP__
#define __MODULE__OPENALINTERFACE_HPP__

// C++ standard library includes
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <EASTL/vector.h>
#include <EASTL/string.h>

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
			ALCdevice* device;			// The current OpenAL device
			ALCcontext* context;		// The current OpenAL context
			Book<ALuint> soundNames;	// The "names" of all playing sounds
			Book<ALuint> clipNames;		// The "names" of all loaded sounds
			Book<uint16_t> pcmData;		// The underlying PCM data
			
			// IMPLEMENTED
			void updateEnvironment();		// Updates positions, velocities, etc.
			void replaySound(Sound*);		// Replays a Sound
			void resumeSound(Sound*);		// Resumes a Sound
			void pauseSound(Sound*);		// Pauses a Sound
			void stopSound(Sound*);			// Stops a Sound
			void setDevice();				// Sets the device
			void setListener(GameObject*);	// Sets the listener GameObject
			
			ALuint getSoundName(Sound*) const;		// Gets the OpenAL "name" of a Sound
			ALuint getClipName(SoundClip*) const;	// Gets the OpenAL "name" of a SoundClip
			
		public:
			OpenALInterface();								// Constructor
			Sound* playSound(SoundClip*,GameObject*);		// Plays a Sound
			SoundClip* loadSoundClip(const eastl::string&, 
									 const eastl::string&);	// Loads SoundClip
			void unloadSoundClip(SoundClip*);				// Unloads SoundClip
	};

}

#endif
