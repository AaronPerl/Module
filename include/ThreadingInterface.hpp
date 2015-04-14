#ifndef __MODULE__THREADINGINTERFACE_HPP__
#define __MODULE__THREADINGINTERFACE_HPP__

#include "Mutex.hpp"
#include "ThreadObject.hpp"

namespace Module {

class ModuleGame;

// The ThreadingInterface class. It manages the spawning of threads as well as the locking/unlocking of mutexes.
// Being an Interface, this class is pure virtual. It is meant to be implemented to perform this functionality.
class ThreadingInterface {
protected:
	ModuleGame* game;
	
	void* getMutexPtr(Mutex& m);				// returns Mutex's object pointer, used to get permission from ThreadingInterface subclasses
	void runThreadObject(ThreadObject* obj);	// run's ThreadObject's run method, used to get permission from ThreadingInterface subclasses
	
	// IMPLEMENT THESE //
	virtual void startThread(ThreadObject* obj) = 0;	// start ThreadObject's thread, call runThreadObject from new thread
	virtual Mutex* createMutex() = 0;					// create mutex
	virtual void lock(Mutex& m) = 0;					// lock mutex
	virtual void unlock(Mutex& m) = 0;					// unlock mutex
public:

	friend class ModuleGame;
};

}

#endif