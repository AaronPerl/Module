#ifndef __MODULE__SERVERSOCKET_HPP__
#define __MODULE__SERVERSOCKET_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

#include <string>
#include <vector>

namespace Module
{

class ServerSocket : ThreadObject
{
protected:
	NetworkInterface* network;
	unsigned short portNumber;
	std::vector<NetworkCallback*> callbacks;

	virtual void run();//When run, the port calls listen to wait for connections. Each connection is passed off to a new client socket.

public:

	unsigned short getPortNumber(){return portNumber;};

	friend class NetworkInterface;
};

}




#endif
