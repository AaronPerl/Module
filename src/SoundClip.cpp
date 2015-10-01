#include "SoundClip.hpp"

using namespace Module;

/** Gets the name of this SoundClip.
 * @return The name of this SoundClip.
*/
const std::string& SoundClip::getName() const
{
	return name;
}
/** Gets the frequecy of this SoundClip, in Hertz.
*/
unsigned int SoundClip::getFrequency() const
{
	return frequency;
}
/** Gets the next unique ID for a SoundClip.
*/
uint16_t SoundClip::getNextUID()
{
	return numInstances++;
}