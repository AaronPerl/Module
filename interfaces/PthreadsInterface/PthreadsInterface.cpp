#include "PthreadsInterface.hpp"
#include "PthreadsThreadData.hpp"
#include <stdexcept>

void Module::PthreadsInterface::startThread(ThreadObject* obj)
{
	int exception;
	PthreadsThreadData* data = new PthreadsThreadData();
	getData(obj) = data;
	exception = pthread_create(&(data->pthread), NULL, PthreadsInterface::startHelper, obj);
	if (exception)
		throw std::runtime_error("Failed to spawn new thread!");
}