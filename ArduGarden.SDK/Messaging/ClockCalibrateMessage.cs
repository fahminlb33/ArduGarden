using System;

namespace ArduGarden.SDK.Messaging
{
    class ClockCalibrateMessage : IMessage
    {
        public DateTime Time { get; set; }

    }
}
