#ifndef __MODULE__THREADINGINTERFACE_HPP__
#define __MODULE__THREADINGINTERFACE_HPP__

#include "Mutex.hpp"
#include "ThreadObject.hpp"

namespace Module {

class ModuleGame;

class ThreadingInterface {
protected:
	void* getMutexPtr(Mutex& m);				// returns Mutex's object pointer, used to get permission from ThreadingInterface subclasses
	void runThreadObject(ThreadObject& obj);	// run's ThreadObject's run method, used to get permission from ThreadingInterface subclasses
	
	// IMPLEMENT THESE //
	virtual void startThread(ThreadObject* obj) = 0;	// start ThreadObject's thread, call runThreadObject from new thread
	virtual void lock(Mutex& m) = 0;					// lock mutex
	virtual void unlock(Mutex& m) = 0;					// unlock mutex
public:

	friend class ModuleGame;
};

}

#endif