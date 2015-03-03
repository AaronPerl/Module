#ifndef __MODULE__NETWORKCALLBACK_HPP__
#define __MODULE__NETWORKCALLBACK_HPP__

#include <string>

namespace Module
{

class NetworkCallback
{
protected:

public:
	virtual void onReceiveConnection(std::string port,std::string clientip) {};
	virtual void onReceiveMessage(std::string port,std::string message) {};//temp, replace with different message type
}

}
#endif
