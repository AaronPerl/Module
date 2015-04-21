#ifndef __MODULE__THREAD_HPP__
#define __MODULE__THREAD_HPP__

namespace Module {

// Subclass in ThreadingInterface implementations to store per-thread data
class ThreadData {
protected:
public:
	friend class ThreadingInterface;
};

}

#endif