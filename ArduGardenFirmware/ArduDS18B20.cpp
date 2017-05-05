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

#include "ArduDS18B20.h"

ArduDS18B20::ArduDS18B20() {
}

void ArduDS18B20::init(OneWire* wire) {
	_ds_wire = wire;
	_ds_wire->search(addr);
	_ds_wire->reset();
}

float ArduDS18B20::getTemperature() {
	_ds_wire->reset();
	_ds_wire->select(addr);
	_ds_wire->write(DS18B20_START, 1);

	delay(1000);

	_ds_wire->reset();
	_ds_wire->select(addr);
	_ds_wire->write(DS18B20_READ_STRATCHPAD);

	for (i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = _ds_wire->read();
	}

	int16_t raw = (data[1] << 8) | data[0];
	byte cfg = (data[4] & 0x60);
	// at lower res, the low bits are undefined, so let's zero them
	if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
	else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
	else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
										  //// default is 12 bit resolution, 750 ms conversion time
	return (float)raw / 16.0;
}