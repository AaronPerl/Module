#ifndef __MODULE__THREADINGINTERFACE_HPP__
#define __MODULE__THREADINGINTERFACE_HPP__

#include "Mutex.hpp"
#include "ThreadObject.hpp"

namespace Module {

class ModuleGame;

class ThreadingInterface {
private:
	virtual void startThread(ThreadObject* obj) = 0;
	virtual void lock(Mutex* m) = 0;
	virtual void unlock(Mutex* m) = 0;
public:
	
	friend class ModuleGame;
};

}

#endif