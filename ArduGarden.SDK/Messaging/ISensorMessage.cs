namespace ArduGarden.SDK.Messaging
{
    public interface ISensorMessage
    {
        SensorType Type { get; set; }
        float Value { get; set; }
    }
}