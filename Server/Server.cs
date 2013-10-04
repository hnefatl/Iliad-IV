using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Server
{
    public class Server
    {
        protected List<Client> Clients;

        protected Thread ClientReceiver;

        protected bool Run;

        public Server()
        {
            ClientReceiver = new Thread(new ParameterizedThreadStart(ClientReceiverFunc));
            

        }

        public void Start(IPEndPoint Local)
        {
            Run = true;
            ClientReceiver.Start(Local);
        }

        protected void ClientReceiverFunc(object oLocal)
        {
            IPEndPoint Local = (IPEndPoint)oLocal;
            TcpListener ServerSocket=new TcpListener(Local);
            ServerSocket.Start(10);

            while (Run)
            {
                TcpClient NewClient=ServerSocket.AcceptTcpClient();

                Clients.Add(new Client());
            }
        }
    }
}