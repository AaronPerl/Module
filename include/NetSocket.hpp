#ifndef __MODULE__NETSOCKET_HPP__
#define __MODULE__NETSOCKET_HPP__


#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

namespace Module
{

class NetSocket : ThreadObject
{
protected:
	ModuleGame* game;
	NetworkInterface* network;



	friend class ModuleGame;
	friend class NetworkInterface;
};

}




#endif
