#ifndef __MODULE__THREADINGINTERFACE_HPP__
#define __MODULE__THREADINGINTERFACE_HPP__

#include "Mutex.hpp"
#include "ThreadObject.hpp"
#include "ThreadData.hpp"

namespace Module {

class ModuleGame;

// The ThreadingInterface class. It manages the spawning of threads as well as the locking/unlocking of mutexes.
// Being an Interface, this class is pure virtual. It is meant to be implemented to perform this functionality.
class ThreadingInterface {
protected:
	ModuleGame* game;
	
	static void runThreadObject(ThreadObject* obj) 	{ obj->run(); }			// runs ThreadObject's run method, used to get permission from ThreadingInterface subclasses
	static ThreadData*& getData(ThreadObject* obj)	{ return obj->data; } 	// returns ThreadObject's ThreadData pointer, subclass ModuleThread to store per-thread data
	
	// IMPLEMENT THESE //
	virtual void startThread(ThreadObject* obj) = 0;	// start ThreadObject's thread, call runThreadObject from new thread
	virtual void stopThread(ThreadObject* obj) = 0;		// stop ThreadObject's thread
	virtual Mutex* createMutex() = 0;					// create mutex
	virtual void destroyMutex(Mutex* m) = 0;			// free mutex from memory
	virtual void lock(Mutex* m) = 0;					// lock mutex
	virtual void unlock(Mutex* m) = 0;					// unlock mutex
public:

	friend class ModuleGame;
};

}

#endif