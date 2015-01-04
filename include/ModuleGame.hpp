#ifndef __MODULEGAME_HPP__
#define __MODULEGAME_HPP__

#include "GraphicsInterface.hpp"

namespace Module {

class ModuleGame {
private:
	GraphicsInterface* graphics;
	
public:
	ModuleGame();
	
	void attachGraphicsInterface(GraphicsInterface* newGraphcis);
	
};

}

#endif