#include "AudioInterface.hpp"

void Module::AudioInterface::printSounds()
{
	std::cout << "Sound Collection:" << std::endl;
	std::cout << " There are " << clips.size() << "." << std::endl;
	for(unsigned int i = 0; i < clips.size(); ++i)
	{
		std::cout << " " << i << ") " << clips[i].getName() << std::endl;
	}
	std::cout << "Currently-playing Sounds:" << std::endl;
	std::cout << " There are " << sounds.size() << "." << std::endl;
	for(unsigned int i = 0; i < sounds.size(); ++i)
	{
		std::cout << " " << i << ") " << sounds[i].getName() << std::endl;
	}
}
