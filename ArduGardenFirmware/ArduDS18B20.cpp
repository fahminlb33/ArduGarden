// 
// 
// 

#include "ArduDS18B20.h"

#ifndef OneWire_h
#include "OneWire.h"
#endif // OneWire_h

OneWire* _ds_wire;

ArduDS18B20::ArduDS18B20() {
}

void ArduDS18B20::init(OneWire* wire) {
	_ds_wire = wire;
	_ds_wire->search(addr);
	_ds_wire->reset();
}

bool ArduDS18B20::isValidAddress() {
	return OneWire::crc8(addr, 7) == addr[7];
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