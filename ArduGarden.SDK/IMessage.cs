﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArduGarden.SDK
{
    interface IMessage
    {
        DateTime Time { get; set; }
    }
}