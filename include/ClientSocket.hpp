#ifndef __MODULE__CLIENTSOCKET_HPP__
#define __MODULE__CLIENTSOCKET_HPP__

#include "ModuleGame.hpp"
#include "ThreadObject.hpp"

#include <string>
#include <vector>

namespace Module
{

class ClientSocket : ThreadObject
{
protected:
	NetworkInterface* network;
	std::vector<NetworkCallback*> callbacks;

	unsigned short portNumber;
	char distantIP[4];
	unsigned short distantPortNumber;

	virtual void run();//Calls recv or equivalent function to wait for a message, calls parent network interface.
public:

	unsigned short getPortNumber(){return portNumber;};
	std::string getDistantIP(){return distantIP;};
	unsigned short getDistantPort(){return distantPortNumber;};

	virtual void connect();//Connects the socket to the distant port and IP.
	virtual void disconnect();//Disconnects the socket from the distant port and IP.
	void sendMessage(std::string message);//Sends message.


	friend class NetworkInterface;
};

}


#endif
