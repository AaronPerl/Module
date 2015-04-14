#include "ThreadingInterface.hpp"

void* Module::ThreadingInterface::getMutexPtr(Mutex& m)
{
	return m.mutex_obj;
}

void Module::ThreadingInterface::runThreadObject(ThreadObject* obj)
{
	obj->run();
}