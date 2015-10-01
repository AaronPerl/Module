#include "OpenALInterface.hpp"
#include "Sound.hpp"
#include "SoundClip.hpp"
#include <stdio.h>
#include <string.h>

using namespace Module;

// Replays a Sound
void OpenALInterface::replaySound(Sound* sound)
{
	alSourceStop(getSoundName(sound));
	alSourcePlay(getSoundName(sound));
}
// Resumes a Sound
void OpenALInterface::resumeSound(Sound* sound)
{
	#ifdef DEBUG
	std::cout << "[AudioInterface] Resuming " << sound->getName() << std::endl;
	#endif
	alSourcePlay(getSoundName(sound));
}
// Pauses a Sound
void OpenALInterface::pauseSound(Sound* sound)
{
	#ifdef DEBUG
	std::cout << "[AudioInterface] Pausing " << sound->getName() << std::endl;
	#endif
	alSourcePause(getSoundName(sound));
}
// Stops a Sound
void OpenALInterface::stopSound(Sound* sound)
{
	#ifdef DEBUG
	std::cout << getSoundName(sound) << "[AudioInterface] Stopping " << sound->getName() << std::endl;
	#endif
	alSourceStop(getSoundName(sound));
}
// Sets the device
void OpenALInterface::setDevice()
{
	device = alcOpenDevice(NULL); // Open the default device
	if (!device)
	{
		#ifdef DEBUG
		std::cerr << "[AudioInterface] Error opening device!" << std::endl;
		#endif
	}
	#ifdef DEBUG
	std::cout << "[AudioInterface] Opened a device successfully." << std::endl;
	#endif
}
// Sets the listener GameObject
void OpenALInterface::setListener(GameObject* gameObject)
{
	if(gameObject == NULL)
	{
		// Initialize the context
		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context))
		{
			#ifdef DEBUG
			std::cerr << "[AudioInterface] Could not make context current" << std::endl;
			#endif
		}
		#ifdef DEBUG
		std::cout << "[AudioInterface] Created a context successfully." << std::endl;
		#endif
	}
}
// Gets the OpenAL "name" of a Sound
ALuint OpenALInterface::getSoundName(Sound* sound) const
{
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		if(&sounds[i] == sound)
		{
			return soundNames[i];
		}
	}
	return -1;
}
// Gets the OpenAL "name" of a SoundClip
ALuint OpenALInterface::getClipName(SoundClip* clip) const
{
	for(unsigned int i = 0; i < clips.size(); ++i)
	{
		if(&clips[i] == clip)
		{
			return clipNames[i];
		}
	}
	return -1;
}
// Constructor
OpenALInterface::OpenALInterface() : AudioInterface()
{
	alutInit(NULL,NULL);
}
// Plays a Sound
Sound* OpenALInterface::playSound(SoundClip* clip, float pitch = 1.0f, float gain = 1.0f)
{
	Sound* toReturn = AudioInterface::playSound(clip);
	// Ensure we actually can create this Sound
	if(toReturn)
	{
		// Create source
		ALuint source;
		alGenSources((ALuint)1, &source);
		
		alSourcef(source, AL_PITCH, (ALfloat)pitch);// Sets pitch
		alSourcef(source, AL_GAIN, (ALfloat)gain);	// Sets gain
		alSource3f(source, AL_POSITION, 0, 0, 0);	// Position = (0,0,0)
		alSource3f(source, AL_VELOCITY, 0, 0, 0);	// Velocity = (0,0,0)
		alSourcei(source, AL_LOOPING, AL_FALSE);	// Looping off
		
		// Look up what buffer "name" this SoundClip represents
		ALuint buffer = getClipName(clip);
		alSourcei(source, AL_BUFFER, buffer);
		soundNames.push_back(source);
		
		alSourcePlay(source);
	}
	return toReturn;
}
// Loads SoundClip
SoundClip* OpenALInterface::loadSoundClip(const std::string& name, const std::string& fileName)
{
	SoundClip* toReturn = AudioInterface::loadSoundClip(name,fileName);
	// Ensure we actually can create this SoundClip
	if(toReturn)
	{
		ALfloat frequency;
		ALsizei size;
		#ifdef DEBUG
		std::cout << "[AudioInterface] Loading \"" << fileName.c_str() << "\"." << std::endl;
		#endif
		uint16_t* temp = (uint16_t*)alutLoadMemoryFromFile(fileName.c_str(), NULL, &size, &frequency);
		
		if(!temp)
		{
			#ifdef DEBUG
			std::cerr << "[AudioInterface] Not a valid file!" << std::endl;
			std::cerr << "[AudioInterface] : ALUT :" << alutGetErrorString(alutGetError()) << std::endl;
			#endif
			return NULL;
		}
		unsigned int dataSize = size/2;
		for(unsigned int i = 0; i < dataSize; i++)
		{
			pcmData.push_back(temp[i]);
		}
		
		ALuint buffer;
		alGenBuffers((ALuint)1, &buffer);
		clipNames.push_back(buffer);
		
		alBufferData(buffer, AL_FORMAT_MONO16, temp, (ALsizei)size, (ALsizei)frequency); // bind data to buffer
		toReturn->setFrequency(frequency*1000);
	}
	return toReturn;
}
// Unloads SoundClip
void OpenALInterface::unloadSoundClip(SoundClip* clip)
{
	
}