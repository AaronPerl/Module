#ifndef __MODULE__GRAPHICSINTERFACE_HPP__
#define __MODULE__GRAPHICSINTERFACE_HPP__

#include "ThreadingInterface.hpp"

namespace Module {

class ModuleGame;

class GraphicsInterface : ThreadObject {
protected:
	unsigned int fps;
	ModuleGame* game;
	
	virtual void start();
	//overrides ThreadObject::run()
	virtual void run();
	
	virtual void createWindow() = 0;
	virtual void renderFrame() = 0;
	virtual unsigned long getMilliseconds() = 0;
public:
	GraphicsInterface() : fps(60) {}
	GraphicsInterface(unsigned int set_fps) : fps(set_fps) {}
	
	friend class ModuleGame;
};

}

#endif