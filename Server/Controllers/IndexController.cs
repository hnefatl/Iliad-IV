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
            Main = new Server(Port);
        }

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult ConnectFailed()
        {
            return View();
        }

        public ActionResult Controller(string Command)
        {
            Models.ControllerModel Model = new Models.ControllerModel();
            if (!string.IsNullOrWhiteSpace(Command))
            {
                // Send the command
                Main.Send(Command);
                // Receive the result
                Model.Output = Main.Receive();
            }

            // Return the display, with the output displayed
            return View(Model);
        }

        [HttpPost]
        public RedirectResult ConnectPressed(Models.IndexModel Model)
        {
            // Create the server
            Main = new Server(Port);
            Main.Start();
            if (!Main.Connect(Model.ID))
            {
                Main.Stop();
                // Server failed to connect
                return Redirect("ConnectFailed");
            }
            // Server connected succesfully
            return Redirect("Controller");
        }
    }
}
