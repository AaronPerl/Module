#include "OpenALInterface.hpp"
#include <stdio.h>
#include <string.h>

using namespace Module;

void OpenALInterface::setDevice()
{
	// Open device handle
	device = alcOpenDevice(NULL); // Open the default device
	if (!device)
	{
		std::cerr << "[AudioInterface] Error opening device!" << std::endl;
	}
	std::cout << "[AudioInterface] Opened a device successfully." << std::endl;
}
void OpenALInterface::setListener(GameObject* gameObject)
{
	if(gameObject == NULL)
	{
		// Initialize the context
		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context))
		{
			std::cerr << "[AudioInterface] Could not make context current" << std::endl;
		}
		std::cout << "[AudioInterface] Created a context successfully." << std::endl;
	}
}
OpenALInterface::OpenALInterface() : AudioInterface()
{
	alutInit(NULL,NULL);
}
Sound* OpenALInterface::playSound(SoundClip* clip)
{
	Sound* toReturn = AudioInterface::playSound(clip);
	// Ensure we actually can create this Sound
	if(toReturn)
	{
		// Create source
		ALuint source;
		alGenSources((ALuint)1, &source);
		
		alSourcef(source, AL_PITCH, 1);				// Pitch of 1
		alSourcef(source, AL_GAIN, 1);				// Gain of 1
		alSource3f(source, AL_POSITION, 0, 0, 0);	// Position = (0,0,0)
		alSource3f(source, AL_VELOCITY, 0, 0, 0);	// Velocity = (0,0,0)
		alSourcei(source, AL_LOOPING, AL_FALSE);	// Looping off
		
		// Look up what buffer "name" this SoundClip represents
		ALuint buffer;
		for(unsigned int i = 0; i < clips.size(); ++i)
		{
			if(&clips[i] == clip)
			{
				buffer = clipNames[i];
				break;
			}
		}		
		alSourcei(source, AL_BUFFER, buffer);
		soundNames.push_back(source);
		alSourcePlay(source);
	}
	return toReturn;
}
Sound* OpenALInterface::playSound(SoundClip* clip, float pitch, float gain)
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
		ALuint buffer;
		for(unsigned int i = 0; i < clips.size(); ++i)
		{
			if(&clips[i] == clip)
			{
				buffer = clipNames[i];
				break;
			}
		}		
		alSourcei(source, AL_BUFFER, buffer);
		soundNames.push_back(source);
		alSourcePlay(source);
	}
	return toReturn;
}
SoundClip* OpenALInterface::loadSoundClip(const std::string& name, const std::string& fileName)
{
	SoundClip* toReturn = AudioInterface::loadSoundClip(name,fileName);
	// Ensure we actually can create this SoundClip
	if(toReturn)
	{
		ALfloat frequency;
		ALsizei size;
		std::cout << "[AudioInterface] Loading \"" << fileName.c_str() << "\"." << std::endl;
		uint16_t* temp = (uint16_t*)alutLoadMemoryFromFile(fileName.c_str(), NULL, &size, &frequency);
		if(!temp)
		{
			std::cerr << "[AudioInterface] Not a valid file!" << std::endl;
			std::cerr << "[AudioInterface] : ALUT :" << alutGetErrorString(alutGetError()) << std::endl;
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
void OpenALInterface::unloadSoundClip(SoundClip* clip)
{
	
}