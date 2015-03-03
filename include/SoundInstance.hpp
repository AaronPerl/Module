#ifndef __MODULE__SOUNDINSTANCE_HPP__
#define __MODULE__SOUNDINSTANCE_HPP__

#include <cstdio>
#include <string>
#include "AudioInterface.hpp"
#include "SoundObject.hpp"

namespace Module
{
	// The SoundInstance represents a single playing of a sound,
	// or, in some instances, the looping of that sound. It points
	// to a specific SoundObject, whose data is being played.
	class SoundInstance
	{
		friend class AudioInterface;
		
		private:
			unsigned int uid;
			SoundObject* soundObject;
			SoundInstance(unsigned int id, SoundObject* so): uid(id), soundObject(so) {}
			
		public:
			const std::string getName()
			{
				char name[20];
				sprintf(name,"%u", uid);
				std::string s(name);
				return soundObject->getName() + "_" + s;
			}
			
	};
}
#endif