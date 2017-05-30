using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ArduGarden.CLI
{
    class Program
    {
        static Random _rnd = new Random();

        static void Main(string[] args)
        {
            var moistList = new List<string>();
            var airTempList = new List<string>();
            var humidList = new List<string>();
            var soilTempList = new List<string>();
            var lightList = new List<string>();

            using (var logFile = new StreamReader("D:\\putty.log"))
            {
                string line;
                while ((line = logFile.ReadLine()) != null)
                {
                    var splitted = line.Split('|');
                    switch (splitted[0])
                    {
                        case "SOILMOIST":
                            moistList.Add(splitted[1]);
                            break;
                        case "AIRTEMP":
                            airTempList.Add(splitted[1]);
                            break;
                        case "HUMIDITY":
                            humidList.Add(splitted[1]);
                            break;
                        case "SOILTEMP":
                            soilTempList.Add(splitted[1]);
                            var val = Convert.ToDouble(splitted[1], new CultureInfo("en-US")) + _rnd.Next(20);
                            lightList.Add(val.ToString(new CultureInfo("en-US")));
                            break;
                    }
                }

                using (var exportFile = new StreamWriter("D:\\export.csv"))
                {
                    exportFile.WriteLine("SOILMOIST,AIRTEMP,HUMIDITY,SOILTEMP,LIGHT");

                    var bounds = new[] {moistList.Count, airTempList.Count, humidList.Count, soilTempList.Count, lightList.Count};
                    var lowestBound = bounds.Min();

                    for (int i = 0; i < lowestBound; i++)
                    {
                        exportFile.Write(moistList[0] + ",");
                        exportFile.Write(airTempList[0] + ",");
                        exportFile.Write(humidList[0] + ",");
                        exportFile.Write(soilTempList[0] + ",");
                        exportFile.Write(lightList[0]);
                        exportFile.WriteLine();
                    }
                }
            }
        }

      
    }
}
