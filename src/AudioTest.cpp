#include "AudioInterface.hpp"
#include "SoundObject.hpp"

int main()
{
	Module::AudioInterface ai;
	
	Module::SoundObject* sound = ai.createSound("explosion",NULL);
	ai.createSound("laser",NULL);
	ai.createSound("murmur",NULL);
	ai.createSound("music",NULL);
	ai.createSound("murmur",NULL);
	
	ai.playSound(sound);
	ai.playSound("music");
	ai.playSound("something that isn't real");
	ai.playSound(sound);
	ai.playSound(sound);
	ai.playSound(sound);
	
	ai.printSoundObjects();
	ai.printSoundInstances();
	
	return 0;
}