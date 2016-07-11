#ifndef __MODULE__EXTENSION_HPP__
#define __MODULE__EXTENSION_HPP__

#include "ModuleDefines.hpp"
#include <EASTL/vector.h>

namespace Module {

/**
 * Extensions are essentially a means to package up the instantiation and
 * attachment of callback objects, as well as the spawning of threads.
 * This allows for Module specific libraries that can easily be included in projects.
 */
class Extension {
protected:
	ModuleGame* game_;
	
	Extension() : game_(NULL) {}
	
	eastl::vector<const char*> componentTypes;
	
	// IMPLEMENT THESE //
	virtual const char* getName() = 0;
	virtual const char* getVersion() = 0;
	
	// These functions are for organizing the instantiation of this extension.
	// These are all called directly before the interfaces are started.
	virtual void registerComponents() = 0;
	virtual void attachGraphicsCallbacks() = 0;
	virtual void attachInputCallbacks() = 0;
	virtual void attachAudioCallbacks() = 0;
	virtual void spawnThreads() = 0;
	
	void setGame(ModuleGame* game);
	void registerComponent(const char* componentName);
	void registerComponent(Component* component);
public:
	const eastl::vector<const char*>& getComponentTypes() { return componentTypes; }

friend class ModuleGame;
friend class ComponentManager;
};

}

#endif