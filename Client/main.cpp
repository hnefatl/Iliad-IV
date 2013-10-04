#include <iostream>
#include <fstream>

#include "Client.h"

bool ReadSettings(const std::string Path, std::string *const TargetIP, std::string *const Port, std::string *const ID);

int main(int argc, char *argv[])
{
	std::string IP, Port, ID;

	if(!ReadSettings("Data.txt", &IP, &Port, &ID))
	{
		return -1;
	}

	while(true)
	{
		Client Main;
		if(!Main.Connect(IP, Port, ID))
		{
			return 1;
		}

		
	}

	return 0;
}

bool ReadSettings(const std::string Path, std::string *const TargetIP, std::string *const Port, std::string *const ID)
{
	std::ifstream In;
	In.open(Path);
	if(!In.good())
	{
		return false;
	}

	std::getline(In, *TargetIP);
	std::getline(In, *Port);
	std::getline(In, *ID);

	In.close();
	return true;
}