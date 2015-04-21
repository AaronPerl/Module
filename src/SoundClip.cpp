#include "SoundClip.hpp"

const std::string& Module::SoundClip::getName() const
{
	return name;
}
uint16_t Module::SoundClip::getNextUID()
{
	return numInstances++;
}