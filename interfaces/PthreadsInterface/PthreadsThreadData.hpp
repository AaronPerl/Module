#ifndef __PTHREADSDATA_HPP__
#define __PTHREADSDATA_HPP__

#include <ThreadData.hpp>

namespace Module {

class PthreadsThreadData;

class PthreadsThreadData : ThreadData {
protected:
	pthread_t pthread;
public:
	friend class PthreadsInterface;
};

}

#endif