#include "NetworkInterface.hpp"

void Module::NetworkInterface::attachCallback(NetworkCallback* callback, unsigned short serverPort)
{
	for(int i = 0; i < servers.size(); i++)
	{
		if(servers[i]->getPortNumber() == serverPort)
		{
			servers[i]->callbacks.push_back(callback);
			callback->server = servers[i];
			break;
		}
	}
}

void Module::NetworkInterface::attachCallback(NetworkCallback* callback, unsigned short clientPort, unsigned short distantPort, std::string distantIP)
{
	for(int i = 0; i < clients.size(); i++)
	{
		if(clients[i]->getPortNumber() == clientPort && clients[i]->getDistantPort() == distantPort && clients[i]->getDistantIP() == distantIP)
		{
			clients[i]->callbacks.push_back(callback);
			callback->client = servers[i];
			break;
		}
	}
}
