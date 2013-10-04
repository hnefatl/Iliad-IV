#include "Networking.h"

#include <sstream>

bool Net::Send(SOCKET Target, std::string Message)
{
	std::stringstream Converter; // StringStream used to convert ints to strings
	std::string MessageSize; // The length of the message, as a string
	std::string MessageSizeSize; // The length of the string representing the length of the message, as a string
	
	// Convert the length of the message to a string
	Converter<<Message.size();
	Converter>>MessageSize;
	Converter.clear();
	// Convert the length of the string representation of the message to a string
	Converter<<MessageSize.size();
	Converter>>MessageSizeSize;

	// Send the size of the message size
	if(!SendPlain(Target, MessageSizeSize))
	{
		// Network error
		return false;
	}
	// Send the size of the message
	if(!SendPlain(Target, MessageSize))
	{
		// Network error
		return false;
	}
	// Send the message itself
	if(!SendPlain(Target, Message))
	{
		// Network error
		return false;
	}

	// Nothing went wrong
	return true;
}
bool Net::SendPlain(SOCKET Target, std::string Message)
{
	unsigned int BytesSent=0; // Variable to hold the total number of bytes sent
	// While there is more data to send
	while(BytesSent!=Message.size())
	{
		// Send the data, store the amount of bytes sent this time
		int Sent=send(Target, &Message[BytesSent], Message.size()-BytesSent, NULL);
		if(Sent<0)
		{
			// Network error
			return false;
		}
		// Increase the number of bytes sent by the number of bytes sent this time
		BytesSent+=(unsigned int)Sent;
	}

	return true;
}

bool Net::Receive(SOCKET Target, std::string *Buffer)
{
	std::stringstream Converter; // Variable used to convert strings to ints
	unsigned int MessageSizeSize; // Variable used to store the length of the string representation fo the legnth of the message
	unsigned int MessageSize; // Variable used to store the length of the message
	
	std::string Temp;
	// Receive one byte - the length of the message length
	if(!ReceivePlain(Target, &Temp, 1))
	{
		// Network error
		return false;
	}
	// Convert the string to an int
	Converter<<Temp;
	Converter>>MessageSizeSize;
	Converter.clear();
	Temp.clear();
	
	// Receive however many bytes constitute the length of the message
	if(!ReceivePlain(Target, &Temp, MessageSizeSize))
	{
		// Network error
		return false;
	}
	// Convert the string to an int
	Converter<<Temp;
	Converter>>MessageSize;
	Temp="";
	
	// Receive however many bytes constitue the message itself
	if(!ReceivePlain(Target, &Temp, MessageSize))
	{
		// Network error
		return false;
	}

	// Store the newly received message
	*Buffer=Temp;

	return true;
}
bool Net::ReceivePlain(SOCKET Target, std::string *Buffer, unsigned int Length)
{
	std::stringstream Message; // Variable to hold the received message in
	unsigned int BytesReceived=0; // Number of bytes received so far

	// While there is more data to recieve
	while(BytesReceived!=Length)
	{
		char Temp[256]; // Variable to hold the data received this time
		// Receive the data, store how many bytes were received
		// Receive x bytes - if Length-BytesReceived is over 255, just receive 255, otherwise receive a full 255
		int Received=recv(Target, Temp, Length-BytesReceived>255?255:Length-BytesReceived, NULL);
		if(Received<=0)
		{
			// Network error
			return false;
		}
		// NULL delimiter
		Temp[Received]='\0';
		// Add the number of bytes received this time to the number of bytes received in total
		BytesReceived+=(unsigned int)Received;
		// Append the newly acquired message to the full message
		Message<<Temp;
	}

	// Store the result in the buffer passed
	*Buffer=Message.str();

	return true;
}
bool Net::ValidIP(std::string IP)
{
	sockaddr_in sa;
	return inet_pton(AF_INET, IP.c_str(), &sa.sin_addr)!=0;
}