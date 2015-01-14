#ifndef __MODULE__MODULEINTERFACE_HPP__
#define __MODULE__MODULEINTERFACE_HPP__

#include "ModuleGame.hpp"

namespace Module {

class ModuleInterface {
protected:
	ModuleGame* game;
	
	virtual void start() = 0;
public:
	friend class ModuleGame;
};

}

#endif