#ifndef __MODULE__NETWORKINTERFACE_HPP__
#define __MODULE__NETWORKINTERFACE_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"
#include "NetworkCallback.hpp"
#include "NetSocket.hpp"

#include <string>

namespace Module
{

class NetworkInterface
{
protected:
	ModuleGame* game;
	NetSocket* sockets;
	NetworkCallback* callbacks;

public:
	//FUNCTIONS
	virtual void openServer(unsigned short port);//Opens server port with the given port number.
	virtual void openClient(unsigned short port);//Opens client port with the given port number.
	virtual void connectClient(unsigned short clientPort, std::string serverIP, unsigned short serverPort);
	//Has the client port with the given number connect to a server port at the target IP.
	virtual void sendMessageAll(unsigned short port, std::string message);//Sends a message to all active connections from this port.
	virtual void sendMessage(unsigned short port, std::string serverIP, unsigned short serverPort, std::string message);
	//Sends a message from this port to a specified IP and port.
	virtual void receiveConnection(unsigned short port,std::string clientIP);//Called by sockets to call onReceiveConnection for all callback objects
	virtual void receiveMessage(unsigned short port,std::string message);

	friend class ModuleGame;
};

}


#endif
