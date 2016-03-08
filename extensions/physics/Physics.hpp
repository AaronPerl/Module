#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <ModuleDefines.hpp>
#include <Extension.hpp>

namespace Module {

/**
 * An extension that incorporates bullet physics into the Module Game Engine.
 */
class Physics : Extension
{	
	// IMPLEMENT THESE //
	virtual const std::string& getName() { return "Bullet Physics Extension"; }
	virtual const std::string& getVersion() { return "0.0.1"; }
	
	// These functions are for organizing the instantiation of callbacks and threads
	virtual void attachGraphicsCallbacks() {}
	virtual void attachInputCallbacks() {}
	virtual void attachAudioCallbacks() {}
	virtual void spawnThreads();
};

}

#endif