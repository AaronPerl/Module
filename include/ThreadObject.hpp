#ifndef __MODULE__THREADABLE_HPP__
#define __MODULE__THREADABLE_HPP__

#include "ThreadData.hpp"

namespace Module {

class ThreadingInterface;

class ThreadObject {
protected:
	virtual void run() = 0;
	ThreadData* data;
public:
	friend class ThreadingInterface;
};

}

#endif