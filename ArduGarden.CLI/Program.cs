using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ArduGarden.CLI
{
    class Program
    {
        static void Main(string[] args)
        {
            var serial = new SerialPort();
            serial.BaudRate = 9600;
            serial.PortName = "COM16";
            serial.Open();

            serial.DataReceived += Serial_DataReceived;

            Console.Read();

            serial.Close();
        }

        private static void Serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var serial = (SerialPort) sender;

            var sb = new StringBuilder();
            while (true)
            {
                var dataLength = serial.BytesToRead;
                var data = new byte[dataLength];
                serial.Read(data, 0, dataLength);

                var line = Encoding.ASCII.GetString(data);
                sb.Append(line);
                if (line.EndsWith("\n"))
                {
                    sb.Remove(sb.Length - 1, 1);
                    break;
                }
            }

            Console.WriteLine(sb.ToString());
        }

    }
}
