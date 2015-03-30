#ifndef __MODULE__NETSOCKET_HPP__
#define __MODULE__NETSOCKET_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

#include <string>

namespace Module
{

class NetSocket : ThreadObject
{
protected:
	ModuleGame* game;
	NetworkInterface* network;
	bool isServer;

	virtual void run();//When run, the port waits

public:

	friend class ModuleGame;
	friend class NetworkInterface;
};

}




#endif
