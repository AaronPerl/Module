#ifndef __PTHREADSINTERFACE_HPP__
#define __PTHREADSINTERFACE_HPP__

// C++ standard library includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

// Module includes
#include <ModuleGame.hpp>
#include <ThreadingInterface.hpp>
#include <ThreadObject.hpp>
#include <ThreadData.hpp>
#include <Mutex.hpp>
#include "PthreadsMutex.hpp"
#include "PthreadsThreadData.hpp"

// Library includes
#include <pthread.h>

namespace Module
{
	class PthreadsInterface : public ThreadingInterface
	{
		protected:
			void startThread(ThreadObject* obj);
			void stopThread(ThreadObject* obj) { pthread_cancel(((PthreadsThreadData*)getData(obj))->pthread); }
			Mutex* createMutex() 	{ return new PthreadsMutex(); }
			void   destroyMutex(Mutex* m) 	{ delete m; }
			void lock(Mutex* m) 	{ ((PthreadsMutex*)m)->lock(); }
			void unlock(Mutex* m) 	{ ((PthreadsMutex*)m)->lock(); }
			
			static void* startHelper(void* obj) { runThreadObject((ThreadObject*) obj); return 0; } // Helper function to pass to pthread_create
		public:
			
		friend class ModuleGame;
	};
}

#endif