#ifndef __MODULE__NETWORKCALLBACK_HPP__
#define __MODULE__NETWORKCALLBACK_HPP__

#include <string>

namespace Module
{

class NetworkCallback
{
protected:
	ClientSocket* client;
	ServerSocket* server;

public:
	virtual void onReceiveConnection(std::string distantIP, unsigned short distantPort) {};
	//Called when a server port receives a connection.
	virtual void onReceiveMessage(std::string message) {};
	//Called when a client port receives a message.
};

}
#endif
