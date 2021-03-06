/*
  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  ----------------------------------------------------------------------
  CHANGES:
  04/05/2017   reduced code size
               created new class ArduDS18B20
*/

#ifndef _ARDUDS18B20_h
#define _ARDUDS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#endif

#ifndef OneWire_h
	#include "OneWire.h"
#endif // OneWire_h

#define DS18B20_START 0x44
#define DS18B20_READ_STRATCHPAD 0xBE

class ArduDS18B20 {
public:
	ArduDS18B20();
	void init(OneWire* wire);
	float getTemperature();

private:
	uint8_t i;
	uint8_t data[12];
	uint8_t addr[8];
	OneWire* _ds_wire;
};

#endif

