#ifndef __MODULE__MODULEGAME_HPP__
#define __MODULE__MODULEGAME_HPP__

#include "GraphicsInterface.hpp"
#include "ThreadingInterface.hpp"
#include "AudioInterface.hpp"

namespace Module {

// The main class of Module. The ModuleGame class represents the core of Module. Its functionality ties together
// that of the different interfaces. End users of Module (game developers) control Module through this class and not
// by accessing interfaces, as those are meant to be abstracted away from users. Setting up a ModuleGame instance should
// be the first thing done in a game that uses Module.
class ModuleGame {
private:
	GraphicsInterface* graphics;
	ThreadingInterface* threading;
public:
	ModuleGame();
	
	void attachGraphicsInterface(GraphicsInterface* newGraphcis);
	void attachThreadingInterface(ThreadingInterface* newThreading);
	
	void startThread(ThreadObject* obj);
	
	Mutex* createMutex() { return threading->createMutex(); }
};

}

#endif