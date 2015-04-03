#include "SoundData.hpp"

const std::string& Module::SoundData::getName() const
{
	return name;
}
uint16_t Module::SoundData::getNextUID()
{
	return numInstances++;
}