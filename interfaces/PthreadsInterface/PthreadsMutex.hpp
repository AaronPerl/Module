#ifndef __PTHREADSMUTEX_HPP__
#define __PTHREADSMUTEX_HPP__

#include <Mutex.hpp>
#include <pthread.h>

namespace Module {

class PthreadsInterface;

class PthreadsMutex : public Mutex {
protected:
	pthread_mutex_t my_mutex;

	void lock() { pthread_mutex_lock(&my_mutex); } ;
	void unlock() { pthread_mutex_lock(&my_mutex); } ;
	
	PthreadsMutex() { pthread_mutex_init(&my_mutex, NULL); }
	~PthreadsMutex() { pthread_mutex_destroy(&my_mutex); }
public:
	friend class PthreadsInterface;
};

}

#endif