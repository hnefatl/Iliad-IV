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

	bool Connect(const std::string &Target, const std::string &Port);

	void inline Send(const std::string &Message) const
	{
		Net::Send(ServerSocket, Message);
	}
	std::string inline Receive() const
	{
		std::string Received;

		Net::Receive(ServerSocket, &Received);

		return Received;
	}

protected:
	SOCKET ServerSocket;
	std::string ServerIP;
};

#endif