#ifndef __MODULE__NETWORKCALLBACK_HPP__
#define __MODULE__NETWORKCALLBACK_HPP__

#include <string>

namespace Module
{

class NetworkCallback
{
protected:

public:
	virtual void onReceiveConnection(unsigned short port,std::string clientip) {};
	//Called when a server port receives a connection.
	virtual void onReceiveMessage(unsigned short port,char* message,int len) {};
	//Called when a client or server port receives a message.
}

}
#endif
