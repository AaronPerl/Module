#ifndef __MODULE__NETWORKINTERFACE_HPP__
#define __MODULE__NETWORKINTERFACE_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

namespace Module
{

class NetworkInterface : ThreadObject
{
protected:
	ModuleGame* game;




	friend class ModuleGame;
};

}


#endif
