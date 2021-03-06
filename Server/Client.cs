﻿using System;
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
        : Networker
    {
        public Socket NetClient { get; protected set; }

        public Client()
        {

        }
        public Client(Socket Client)
        {
            this.NetClient = Client;
            IO = new NetworkStream(Client);
        }
    }
}