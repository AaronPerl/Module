#ifndef __MODULE__MUTEX_HPP__
#define __MODULE__MUTEX_HPP__

namespace Module {

class ThreadingInterface;

// Subclass in ThreadingInterface implementations to store per-mutex data
class Mutex {
protected:
public:
	friend class ThreadingInterface;
};

}

#endif