#ifndef __MODULE__MODULEGAME_HPP__
#define __MODULE__MODULEGAME_HPP__

namespace Module {
	
class GraphicsInterface;
class ThreadingInterface;

class ModuleGame {
private:
	GraphicsInterface* graphics;
	ThreadingInterface* threading;
public:
	ModuleGame();
	
	void attachGraphicsInterface(GraphicsInterface* newGraphcis);
	void attachThreadingInterface(ThreadingInterface* newThreading);
	
	void startThread(ThreadObject* obj);
};

}

#endif