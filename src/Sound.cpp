#include "Sound.hpp"

using namespace Module;

/** Replays the Sound from the beginning.
*/
void Sound::replay()
{
	audio->replaySound(this);
}
/** Resumes the Sound from where it was last paused.
*/
void Sound::resume()
{
	audio->resumeSound(this);
}
/** Pauses a Sound.
*/
void Sound::pause()
{
	audio->pauseSound(this);
}
/** Stops a Sound (pausing it, and setting it back to the beginning).
*/
void Sound::stop()
{
	audio->stopSound(this);
}
/** Sets the time of this Sound.
 * @param t An unsigned long representing the time of the sound.
*/
void Sound::setTime(const unsigned long t)
{
	time = t;
}
/** Gets the name of this Sound.
 * @return The name of this Sound.
*/
const std::string Sound::getName() const
{
	char name[20];
	sprintf(name,"%u", uid);
	std::string s(name);
	return soundClip->getName() + "_" + s;
}
/** Gets the current time of this Sound.
 * @return An unsigned long, representing the current time of this Sound.
*/
unsigned long Sound::getTime() const
{
	return time;
}
/** Plays a Sound.
 * @return A pointer to the Sound, which is currently playing.
*/
SoundClip* Sound::getSoundClip() const
{
	return soundClip;
}