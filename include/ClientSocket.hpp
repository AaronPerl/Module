#ifndef __MODULE__CLIENTSOCKET_HPP__
#define __MODULE__CLIENTSOCKET_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

#include <string>

namespace Module
{

class ClientSocket : ThreadObject
{
protected:
	ModuleGame* game;
	NetworkInterface* network;

	unsigned short portNumber;
	std::string distantIP;
	unsigned short distantPortNumber;

	char* sendBuf;
	int sendBufLen;

	virtual void run();//Calls recv or equivalent function to wait for a message, calls parent network interface.
public:

	unsigned short getPortNumber(){return portNumber;};

	virtual void connect();//Connects the socket to the distant port and IP.
	virtual void disconnect();//Disconnects the socket from the distant port and IP.
	void sendMessage(char* message, int len);//Adds message byte array to send buffer


	friend class NetworkInterface;
};

}


#endif
