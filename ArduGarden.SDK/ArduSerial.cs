using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArduGarden.SDK
{
    public class ArduSerial
    {
        //private static void Serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        //{
        //    var serial = (SerialPort)sender;

        //    var sb = new StringBuilder();
        //    while (true)
        //    {
        //        var dataLength = serial.BytesToRead;
        //        var data = new byte[dataLength];
        //        serial.Read(data, 0, dataLength);

        //        var line = Encoding.ASCII.GetString(data);
        //        sb.Append(line);
        //        if (line.EndsWith("\n"))
        //        {
        //            sb.Remove(sb.Length - 1, 1);
        //            break;
        //        }
        //    }

        //    Console.WriteLine(sb.ToString());
        //}

    }
}
