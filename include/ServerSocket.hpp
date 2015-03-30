#ifndef __MODULE__SERVERSOCKET_HPP__
#define __MODULE__SERVERSOCKET_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

#include <string>

namespace Module
{

class ServerSocket : ThreadObject
{
protected:
	ModuleGame* game;
	NetworkInterface* network;
	unsigned short portNumber;

	virtual void run();//When run, the port calls listen to wait for connections. Each connection is passed off to a new client socket.

public:

	unsigned short getPortNumber(){return portNumber;};

	friend class NetworkInterface;
};

}




#endif
