#include "SoundClip.hpp"

using namespace Module;

const std::string& SoundClip::getName() const
{
	return name;
}
unsigned int SoundClip::getFrequency() const
{
	return frequency;
}
uint16_t SoundClip::getNextUID()
{
	return numInstances++;
}