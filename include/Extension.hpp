#ifndef __MODULE__EXTENSION_HPP__
#define __MODULE__EXTENSION_HPP__

#include "ModuleDefines.hpp"

namespace Module {

/**
 * Extensions are essentially a means to package up the instantiation and
 * attachment of callback objects, as well as the spawning of threads.
 * This allows for Module specific libraries that can easily be included in projects.
 */
class Extension {
protected:
	ModuleGame* game_;
	Extension(ModuleGame* game) { game_ = game; }
	
	// IMPLEMENT THESE //
	virtual const std::string& getName() = 0;
	virtual const std::string& getVersion() = 0;
	
	// These functions are for organizing the instantiation of callbacks and threads
	virtual void attachGraphicsCallbacks() = 0;
	virtual void attachInputCallbacks() = 0;
	virtual void attachAudioCallbacks() = 0;
	virtual void spawnThreads() = 0;
public:

};

}

#endif