using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Text;

namespace Server
{
    public class Networker
    {
        protected NetworkStream IO;

        public virtual string Receive()
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
        public virtual string ReceivePlain(int Bytes)
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

        public virtual void Send(string Message)
        {
            string Data = string.Empty;
            Data += Convert.ToString(Convert.ToString(Message.Length).Length); // Size of message size
            Data += Convert.ToString(Message.Length); // Size of message
            Data += Message; // Message
            SendPlain(Data);
        }
        public virtual void SendPlain(string Message)
        {
            byte[] Data = Encoding.UTF8.GetBytes(Message);
            bool WrittenSuccesfully = false;
            while (!WrittenSuccesfully)
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