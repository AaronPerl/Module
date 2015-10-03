#include <iostream>
#include "ModuleDefines.hpp"

#ifdef DEBUG

void Module::Log(const std::string& info)
{
	std::cout << info << std::endl;
}

#else

void Module::Log(const std::string& info)
{
}
	
#endif