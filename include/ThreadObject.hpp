#ifndef __MODULE__THREADABLE_HPP__
#define __MODULE__THREADABLE_HPP__

namespace Module {

class ThreadingInterface;

class ThreadObject {
protected:
	virtual void run() = 0;
public:

	friend class ThreadingInterface;
};

}

#endif