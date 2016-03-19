#include "ModuleDefines.hpp"
#include <EASTL/allocator.h>

#ifdef DEBUG

void Module::Log(const eastl::string& info)
{
	std::cout << info << std::endl;
}

#else

void Module::Log(const eastl::string& info)
{
}
	
#endif

std::ostream& operator<< (std::ostream& o, const eastl::string& s)
{
	return (o << s.c_str());
}

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return operator new[](size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return operator new[](size);
}