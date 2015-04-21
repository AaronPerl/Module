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
class Sound;
class SoundClip;
// The AudioInterface is one of Module's four core interfaces,
// and handles its titular audio. It may be used to load and
// or play sounds.
class OpenALInterface : AudioInterface
{
	protected:
		// REPRESENTATION
		Book<ALuint> soundNames;	// The "names" of all playing sounds
		Book<ALuint> clipNames;		// The "names" of all loaded sounds
		
};

}

#endif
