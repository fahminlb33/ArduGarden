using System;

namespace ArduGarden.SDK.Messaging
{
    public class SensorMessage : IMessage, ISensorMessage
    {
        public DateTime Time { get; set; }
        public SensorType Type { get; set; }
        public float Value { get; set; }
    }
}
