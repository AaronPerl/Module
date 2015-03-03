#ifndef __MODULE__SOUNDOBJECT_HPP__
#define __MODULE__SOUNDOBJECT_HPP__

#include <string>
#include "AudioInterface.hpp"

namespace Module
{
	// The SoundObject represents a single sound's data, which
	// is stored in the AudioInterface, and which is read from by
	// SoundInstances, which represent the actual playing of sounds.
	class SoundObject
	{
		friend class AudioInterface;
		
		protected:
			std::string name;
			unsigned int numInstances;
			SoundObject(std::string n, uint16_t* d): name(n) {}
			
		public:
			const std::string getName()	{	return name;	}
	};
}
#endif