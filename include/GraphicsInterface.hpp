#ifndef __MODULE__GRAPHICSINTERFACE_HPP__
#define __MODULE__GRAPHICSINTERFACE_HPP__

#include "ThreadObject.hpp"

namespace Module {

class ModuleGame;

class GraphicsInterface : ThreadObject {
protected:
	unsigned int fps;
	ModuleGame* game;
	
	void start();
	void run(); //overrides ThreadObject::run()
	
	// IMPLEMENT THESE //
	virtual void createWindow() = 0; 				// initialization and window creation
	virtual void renderFrame() = 0;					// render individual frame
	virtual unsigned long getMilliseconds() = 0;	// get time since initialization
public:
	GraphicsInterface() : fps(60) {}
	GraphicsInterface(unsigned int set_fps) : fps(set_fps) {}
	
	friend class ModuleGame;
};

}

#endif