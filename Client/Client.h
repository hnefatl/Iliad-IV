#ifndef _CLIENT_H
#define _CLIENT_H

#include <string>

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>

#include "Networking.h"

class Client
{
public:
	Client();

	bool Connect(const std::string &Target, const std::string &Port, const std::string &ID);

	void inline Send(const std::string &Message) const
	{
		Net::Send(ServerSocket, Message);
	}
	bool inline Receive(std::string *const Message) const
	{
		return Net::Receive(ServerSocket, Message);
	}

protected:
	SOCKET ServerSocket;
	std::string ServerIP;
};

#endif