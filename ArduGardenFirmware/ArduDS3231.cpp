/*
  DS3231.cpp - Arduino/chipKit library support for the DS3231 I2C Real-Time Clock
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to easily interface and use the DS3231 RTC with
  an Arduino or chipKit.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.

  ----------------------------------------------------------------------
  CHANGES:
  04/05/2017   reduced code size
			   removed unused calculations
			   removed unused to string converters
			   removed hardware spesific functions
			   create new class ArduDS3231
*/

#include "ArduDS3231.h"

/* DateTime class body */
DateTime::DateTime()
{
	this->year = 2014;
	this->mon = 1;
	this->date = 1;
	this->hour = 0;
	this->min = 0;
	this->sec = 0;
	this->dow = 3;
}

ArduDS3231::ArduDS3231() {}

DateTime ArduDS3231::getDateTime()
{
	DateTime t;
	_burstRead();
	t.sec = _decode(_burstArray[0]);
	t.min = _decode(_burstArray[1]);
	t.hour = _decodeH(_burstArray[2]);
	t.dow = _burstArray[3];
	t.date = _decode(_burstArray[4]);
	t.mon = _decode(_burstArray[5]);
	t.year = _decodeY(_burstArray[6]) + 2000;
	return t;
}

void ArduDS3231::setTime(uint8_t hour, uint8_t min, uint8_t sec)
{
	if (((hour >= 0) && (hour<24)) && ((min >= 0) && (min<60)) && ((sec >= 0) && (sec<60)))
	{
		_writeRegister(REG_HOUR, _encode(hour));
		_writeRegister(REG_MIN, _encode(min));
		_writeRegister(REG_SEC, _encode(sec));
	}
}

void ArduDS3231::setDate(uint8_t date, uint8_t mon, uint16_t year)
{
	if (((date>0) && (date <= 31)) && ((mon>0) && (mon <= 12)) && ((year >= 2000) && (year<3000)))
	{
		year -= 2000;
		_writeRegister(REG_YEAR, _encode(year));
		_writeRegister(REG_MON, _encode(mon));
		_writeRegister(REG_DATE, _encode(date));
	}
}

void ArduDS3231::setDOW()
{
	int dow;
	byte mArr[12] = { 6,2,2,5,0,3,5,1,4,6,2,4 };
	DateTime _t = getDateTime();

	dow = (_t.year % 100);
	dow = dow*1.25;
	dow += _t.date;
	dow += mArr[_t.mon - 1];
	if (((_t.year % 4) == 0) && (_t.mon<3))
		dow -= 1;
	while (dow>7)
		dow -= 7;
	_writeRegister(REG_DOW, dow);
}

/* Private */
void	ArduDS3231::_sendStart(byte addr)
{
	pinMode(PIN_WIRE_SDA, OUTPUT);
	digitalWrite(PIN_WIRE_SDA, HIGH);
	digitalWrite(PIN_WIRE_SCL, HIGH);
	digitalWrite(PIN_WIRE_SDA, LOW);
	digitalWrite(PIN_WIRE_SCL, LOW);
	shiftOut(PIN_WIRE_SDA, PIN_WIRE_SCL, MSBFIRST, addr);
}

void	ArduDS3231::_sendStop()
{
	pinMode(PIN_WIRE_SDA, OUTPUT);
	digitalWrite(PIN_WIRE_SDA, LOW);
	digitalWrite(PIN_WIRE_SCL, HIGH);
	digitalWrite(PIN_WIRE_SDA, HIGH);
	pinMode(PIN_WIRE_SDA, INPUT);
}

void	ArduDS3231::_sendNack()
{
	pinMode(PIN_WIRE_SDA, OUTPUT);
	digitalWrite(PIN_WIRE_SCL, LOW);
	digitalWrite(PIN_WIRE_SDA, HIGH);
	digitalWrite(PIN_WIRE_SCL, HIGH);
	digitalWrite(PIN_WIRE_SCL, LOW);
	pinMode(PIN_WIRE_SDA, INPUT);
}

void	ArduDS3231::_sendAck()
{
	pinMode(PIN_WIRE_SDA, OUTPUT);
	digitalWrite(PIN_WIRE_SCL, LOW);
	digitalWrite(PIN_WIRE_SDA, LOW);
	digitalWrite(PIN_WIRE_SCL, HIGH);
	digitalWrite(PIN_WIRE_SCL, LOW);
	pinMode(PIN_WIRE_SDA, INPUT);
}

void	ArduDS3231::_waitForAck()
{
	pinMode(PIN_WIRE_SDA, INPUT);
	digitalWrite(PIN_WIRE_SCL, HIGH);
	while (digitalRead(PIN_WIRE_SDA) == HIGH) {}
	digitalWrite(PIN_WIRE_SCL, LOW);
}

uint8_t ArduDS3231::_readByte()
{
	pinMode(PIN_WIRE_SDA, INPUT);

	uint8_t value = 0;
	uint8_t currentBit = 0;

	for (int i = 0; i < 8; ++i)
	{
		digitalWrite(PIN_WIRE_SCL, HIGH);
		currentBit = digitalRead(PIN_WIRE_SDA);
		value |= (currentBit << 7 - i);
		delayMicroseconds(1);
		digitalWrite(PIN_WIRE_SCL, LOW);
	}
	return value;
}

void ArduDS3231::_writeByte(uint8_t value)
{
	pinMode(PIN_WIRE_SDA, OUTPUT);
	shiftOut(PIN_WIRE_SDA, PIN_WIRE_SCL, MSBFIRST, value);
}

uint8_t	ArduDS3231::_decode(uint8_t value)
{
	uint8_t decoded = value & 127;
	decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
	return decoded;
}

uint8_t ArduDS3231::_decodeH(uint8_t value)
{
	if (value & 128)
		value = (value & 15) + (12 * ((value & 32) >> 5));
	else
		value = (value & 15) + (10 * ((value & 48) >> 4));
	return value;
}

uint8_t	ArduDS3231::_decodeY(uint8_t value)
{
	uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
	return decoded;
}

uint8_t ArduDS3231::_encode(uint8_t value)
{
	uint8_t encoded = ((value / 10) << 4) + (value % 10);
	return encoded;
}
