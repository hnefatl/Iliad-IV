#include "Client.h"

#include <iostream>

Client::Client()
{

}

bool Client::Connect(const std::string &Target, const std::string &Port)
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
			break;
		}
	}

	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, p->ai_addr, s, sizeof(s));
	ServerIP=std::string(s);
	freeaddrinfo(ServerInfo);
	return true;
}