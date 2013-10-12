using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Server
{
    public class Server
    {
        protected Socket Listener;
        protected Client Connection;
        int Port;

        public Server(int Port)
        {
            this.Port = Port;
            Listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public void Start()
        {
            lock (Listener)
            {
                Listener.Bind(new IPEndPoint(IPAddress.Any, Port));
                Listener.Listen(10);
            }
        }
        public void Stop()
        {
            lock (Listener)
            {
                Listener.Close();
            }
        }

        public bool Connect(string ID)
        {
            bool Stoppable = true;
            Thread Stopper = new Thread(new ThreadStart(() =>
            {
                Thread.Sleep(10 * 1000);
                try
                {
                    if (Stoppable)
                    {
                        Listener.EndConnect(null);
                    }
                }
                catch
                {

                }
            }));
            try
            {
                Stopper.Start();
                while (Connection == null)
                {
                    Client NewClient = new Client(Listener.Accept());
                    Stoppable = false;
                    Stopper.Abort();
                    string ClientID = NewClient.Receive();
                    if (ClientID == ID)
                    {
                        // Match
                        NewClient.Send("1");
                        Connection = NewClient;
                        return true;
                    }
                    else
                    {
                        // Invalid client
                        NewClient.Send("0");
                    }
                }
            }
            catch
            {
                return false;
            }

            return false;
        }

        public string Receive()
        {
            return Connection.Receive();
        }
        public void Send(string Message)
        {
            Connection.Send(Message);
        }
    }
}