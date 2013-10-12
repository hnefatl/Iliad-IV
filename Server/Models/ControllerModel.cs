using System;

namespace Server.Models
{
    public class ControllerModel
    {
        public ControllerModel()
        {
            Output = string.Empty;
        }

        public string Command { get; set; }
        public string Output { get; set; }
    }
}