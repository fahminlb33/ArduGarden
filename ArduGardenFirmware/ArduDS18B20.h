// ArduDS18B20.h

#ifndef _ARDUDS18B20_h
#define _ARDUDS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
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
	bool isValidAddress();
	float getTemperature();

private:
	uint8_t i;
	uint8_t data[12];
	uint8_t addr[8];
	OneWire* _ds_wire;
};

#endif

