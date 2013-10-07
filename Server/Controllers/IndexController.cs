using System;
using System.Collections.Generic;
using System.IO;
using System.Web;
using System.Web.Mvc;

namespace Server.Controllers
{
    public class IndexController : Controller
    {
        protected Server Main;
        protected int Port;

        public IndexController()
        {
            Port = 34652;
        }

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult ConnectFailed()
        {
            return View();
        }

        public ActionResult Controller()
        {
            return View();
        }

        [HttpPost]
        public RedirectResult ConnectPressed(Models.IndexModel Model)
        {
            Main = new Server(Port);
            Main.Start();
            if (!Main.Connect(Model.ID))
            {
                Main.Stop();
                return Redirect("ConnectFailed");
            }
            return Redirect("Controller");
        }
    }
}
