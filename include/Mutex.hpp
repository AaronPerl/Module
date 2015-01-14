#ifndef __MODULE__MUTEX_HPP__
#define __MODULE__MUTEX_HPP__

namespace Module {

class ThreadingInterface;

class Mutex {
protected:
	void* mutex_obj;
public:

	friend class ThreadingInterface;
};

}

#endif