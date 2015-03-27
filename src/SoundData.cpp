#include "SoundData.hpp"

const std::string Module::SoundData::getName()
{
	return name;
}
const uint16_t Module::SoundData::getNextUID()
{
	return numInstances++;
}
