#ifndef __MODULE__NETWORKINTERFACE_HPP__
#define __MODULE__NETWORKINTERFACE_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"
#include "NetworkCallback.hpp"
#include "NetSocket.hpp"

#include <string>

namespace Module
{

class NetworkInterface : ThreadObject
{
protected:
	ModuleGame* game;
	NetSocket* sockets;

public:

	void openServer(std::string port);
	void openClient(std::string port);
	void connectClient(std::string clientPort, std::string serverIP, std::string serverPort);


	friend class ModuleGame;
};

}


#endif
