/*
  HW_AVR.h - Arduino/chipKit library support for the DS3231 I2C Real-Time Clock
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
  04/05/2017   ORIGINAL VERSION
*/

void ArduDS3231::begin()
{
	if ((PIN_WIRE_SDA == SDA) and (PIN_WIRE_SCL == SCL))
	{
		_use_hw = true;
		// activate internal pullups for twi.
		digitalWrite(SDA, HIGH);
		digitalWrite(SCL, HIGH);
		//delay(1);  // Workaround for a linker bug

		// initialize twi prescaler and bit rate
		cbi(TWSR, TWPS0);
		cbi(TWSR, TWPS1);
		TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;

		// enable twi module, acks, and twi interrupt
		TWCR = _BV(TWEN) | _BV(TWIE)/* | _BV(TWEA)*/;
	}
	else
	{
		_use_hw = false;
		pinMode(PIN_WIRE_SCL, OUTPUT);
	}
}

void ArduDS3231::_burstRead()
{
	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = 0;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

																					// Read data starting from start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_R;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		for (int i = 0; i<7; i++)
		{
			TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);								// Send ACK and clear TWINT to proceed
			while ((TWCR & _BV(TWINT)) == 0) {};									// Wait for TWI to be ready
			_burstArray[i] = TWDR;
		}
		TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(0);
		_waitForAck();
		_sendStart(DS3231_ADDR_R);
		_waitForAck();

		for (int i = 0; i<7; i++)
		{
			_burstArray[i] = _readByte();
			if (i<6)
				_sendAck();
			else
				_sendNack();
		}
		_sendStop();
	}
}

uint8_t ArduDS3231::_readRegister(uint8_t reg)
{
	uint8_t	readValue = 0;

	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = reg;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

																					// Read data starting from start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_R;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Send ACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		readValue = TWDR;
		TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(reg);
		_waitForAck();
		_sendStart(DS3231_ADDR_R);
		_waitForAck();
		readValue = _readByte();
		_sendNack();
		_sendStop();
	}
	return readValue;
}

void ArduDS3231::_writeRegister(uint8_t reg, uint8_t value)
{
	if (_use_hw)
	{
		// Send start address
		TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = DS3231_ADDR_W;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = reg;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
		TWDR = value;
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);									// Send STOP
	}
	else
	{
		_sendStart(DS3231_ADDR_W);
		_waitForAck();
		_writeByte(reg);
		_waitForAck();
		_writeByte(value);
		_waitForAck();
		_sendStop();
	}
}

