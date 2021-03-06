#include "Client.h"

#include <iostream>

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>

Client::Client()
{

}
Client::~Client()
{
	WSACleanup();
}

bool Client::Connect(const std::string &Target, const std::string &Port, const std::string &ID)
{
	std::cout<<"Beginning connect...";
	WSAData Data;

	if(WSAStartup(MAKEWORD(1, 1), &Data)!=0)
	{
		return false;
	}

	addrinfo *ServerInfo, Hints;

	memset(&Hints, 0, sizeof(Hints));
	Hints.ai_family=AF_UNSPEC;
	Hints.ai_socktype=SOCK_STREAM;

	int Rcv;
	if((Rcv=getaddrinfo(Target.c_str(), Port.c_str(), &Hints, &ServerInfo))!=0)
	{
		return false;
	}

	addrinfo *p=NULL;
	// Keep trying to connect
	while(true)
	{
		for(p=ServerInfo; p!=NULL; p=ServerInfo->ai_next)
		{
			if((ServerSocket=socket(p->ai_family, p->ai_socktype, p->ai_protocol))==-1)
			{
				continue;
			}

			if(connect(ServerSocket, p->ai_addr, p->ai_addrlen)==-1)
			{
				continue;
			}

			break;
		}

		if(p!=NULL)
		{
			// Connected to the server - attempt ID validation
			Send(ID);
			std::string Result;
			if(Receive(&Result))
			{
				if(Result=="1")
				{
					// Succesful connection
					std::cout<<"Good connection made."<<std::endl;
					break;
				}
				else
				{
					// Wait 10 seconds to ease off the server
					std::cout<<"Bad connection made."<<std::endl;
					Sleep(10000);
				}
			}
		}
	}

	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, p->ai_addr, s, sizeof(s));
	ServerIP=std::string(s);
	freeaddrinfo(ServerInfo);

	return true;
}