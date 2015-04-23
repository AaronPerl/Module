#include "Sound.hpp"

using namespace Module;

void Sound::replay()
{
	audio->replaySound(this);
}
void Sound::resume()
{
	audio->resumeSound(this);
}
void Sound::pause()
{
	audio->pauseSound(this);
}
void Sound::stop()
{
	audio->stopSound(this);
}
void Sound::setTime(const unsigned long t)
{
	time = t;
}
const std::string Sound::getName() const
{
	char name[20];
	sprintf(name,"%u", uid);
	std::string s(name);
	return soundClip->getName() + "_" + s;
}
unsigned long Sound::getTime() const
{
	return time;
}
SoundClip* Sound::getSoundClip() const
{
	return soundClip;
}