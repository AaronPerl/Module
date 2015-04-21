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
	Book<ServerSocket*> servers;
	Book<ClientSocket*> clients;

public:
	//FUNCTIONS
	virtual void sendMessageUDP(unsigned short port, std::string distantIP, unsigned short distantPort, std::string message);
	//Sends a message to a distant IP and port, message must be less than 256 bytes.
	virtual void listenPortUDP(unsigned short port);//Instructs interface to listen to the given port for UDP datagrams
	virtual void openServerTCP(unsigned short port);//Opens server port with the given port number.
	virtual void closeServerTCP(unsigned short port);//Closes server port with given port number.
	virtual void connectClientTCP(unsigned short clientPort, std::string distantIP, unsigned short distantPort);
	//Has the client port with the given number connect to a server port at the target IP.
	virtual void disconnectClientTCP(unsigned short clientPort, std::string distantIP, unsigned short distantPort);
	//Disconnects the client port with the given settings
	virtual void sendMessageTCP(unsigned short port, std::string serverIP, unsigned short serverPort, std::string message);
	//Sends a message from this port to a specified IP and port.
	void attachCallback(NetworkCallback* callback, unsigned short serverPort);//Attaches callback to server port
	void attachCallback(NetworkCallback* callback, unsigned short clientPort, unsigned short distantPort, std::string distantIP);
	//Attaches callback to client port
	friend class ModuleGame;
};

}


#endif
