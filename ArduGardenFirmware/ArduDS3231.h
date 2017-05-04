// ArduDS3231.h

#ifndef _ARDUDS3231_h
#define _ARDUDS3231_h

#if defined(__AVR__)
#include "Arduino.h"
#include "HW_AVR_defines.h"
#endif

#define DS3231_ADDR_R	0xD1
#define DS3231_ADDR_W	0xD0
#define DS3231_ADDR		0x68

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

class DateTime
{
public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;

	DateTime();
};

class ArduDS3231
{
public:
	ArduDS3231();
	void	begin();
	void	setTime(uint8_t hour, uint8_t min, uint8_t sec);
	void	setDate(uint8_t date, uint8_t mon, uint16_t year);
	void	setDOW();

	DateTime  getDateTime();

private:
	uint8_t _burstArray[7];
	boolean	_use_hw;

	void	_sendStart(byte addr);
	void	_sendStop();
	void	_sendAck();
	void	_sendNack();
	void	_waitForAck();
	uint8_t	_readByte();
	void	_writeByte(uint8_t value);
	void	_burstRead();
	uint8_t	_readRegister(uint8_t reg);
	void 	_writeRegister(uint8_t reg, uint8_t value);
	uint8_t	_decode(uint8_t value);
	uint8_t	_decodeH(uint8_t value);
	uint8_t	_decodeY(uint8_t value);
	uint8_t	_encode(uint8_t vaule);
};

#endif

