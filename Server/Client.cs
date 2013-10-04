using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Web;
using System.IO;
using System.Text;

namespace Server
{
    public class Client
    {
        protected TcpClient Client;
        protected NetworkStream IO;

        public Client()
        {

        }
        public Client(TcpClient Client)
        {
            this.Client = Client;
            IO = new NetworkStream(Client.Client);
        }

        public string Receive()
        {
            string Message = string.Empty;
            int MessageSize = 0;
            int MessageSizeSize = 0;

            try
            {
                MessageSizeSize = Convert.ToInt32(ReceivePlain(1)); // Read the length of the length of the message
                MessageSize = Convert.ToInt32(ReceivePlain(MessageSizeSize)); // Read the length of the message
                Message = ReceivePlain(MessageSize); // Read the message itself
            }
            catch
            {
                return null;
            }

            return Message;
        }
        public string ReceivePlain(int Bytes)
        {
            string Result = string.Empty;

            byte[] Buffer = new byte[Bytes];

            int Received = 0;
            while (Received != Bytes)
            {
                lock (IO)
                {
                    try
                    {
                        Received += IO.Read(Buffer, Received, Bytes - Received);
                    }
                    catch (IOException)
                    {
                        // Read timeout hit - no matter
                    }
                }
            }

            Result = Encoding.UTF8.GetString(Buffer);

            return Result;
        }

        public void Send(string Message)
        {
            SendPlain(Convert.ToString(Convert.ToString(Message.Length).Length)); // Send size of message size
            SendPlain(Convert.ToString(Message.Length)); // Send size of message
            SendPlain(Message); // Send message
        }
        public void SendPlain(string Message)
        {
            byte[] Data = Encoding.UTF8.GetBytes(Message);
            bool WrittenSuccesfully = true;
            while (WrittenSuccesfully)
            {
                lock (IO)
                {
                    try
                    {
                        IO.Write(Data, 0, Data.Length);
                        WrittenSuccesfully = true;
                    }
                    catch (IOException)
                    {
                        // Write timeout hit - no matter
                        WrittenSuccesfully = false;
                    }
                }
            }
        }
    }
}