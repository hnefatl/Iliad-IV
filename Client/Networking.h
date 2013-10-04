#ifndef _NETWORKING_H
#define _NETWORKING_H

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>

#include <string>

namespace Net
{
	bool Send(SOCKET Target, std::string Message);
	bool SendPlain(SOCKET Target, std::string Message);

	bool Receive(SOCKET Target, std::string *Buffer);
	bool ReceivePlain(SOCKET Target, std::string *Buffer, unsigned int Length);

	bool ValidIP(std::string Input);
};
#endif