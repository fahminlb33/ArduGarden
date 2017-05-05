/*
	FILE: 		idDHTLib.cpp
	VERSION: 	0.0.3
	PURPOSE: 	Interrupt driven Lib for DHT11 and DHT22 with Arduino.
	LICENCE:	GPL v3 (http://www.gnu.org/licenses/gpl.html)
	DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf
	DATASHEET: http://www.adafruit.com/datasheets/DHT22.pdf
	
	Based on idDHT11 library: https://github.com/niesteszeck/idDHT11
	Based on DHTLib library: http://playground.arduino.cc/Main/DHTLib
	Based on code proposed: http://forum.arduino.cc/index.php?PHPSESSID=j6n105kl2h07nbj72ac4vbh4s5&topic=175356.0
	
	Changelog:
		v 0.0.1
			fork from idDHT11 lib
			change names to idDHTLib
			added DHT22 functionality
		v 0.0.2
			Optimization on shift var (pylon from Arduino Forum)
		v 0.0.3
			Timing correction to finally work properly on DHT22
			(Dessimat0r from Arduino forum)

	----------------------------------------------------------------------
	CHANGES:
	04/05/2017   reduced code size
	             removed unused calculations
				 renamed class to ArduDHT11
*/

#ifndef _ARDUDHT11_h
#define _ARDUDHT11_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#endif

// state codes
#define DHT11_OK		    0
#define DHT11_ACQUIRING		1
#define DHT11_ACQUIRED		2
#define DHT11_RESPONSE_OK	3

// error codes
#define DHT11_ERROR_CHECKSUM		-1
#define DHT11_ERROR_TIMEOUT			-2
#define DHT11_ERROR_ACQUIRING		-3
#define DHT11_ERROR_DELTA			-4
#define DHT11_ERROR_NOTSTARTED		-5

#define DHT11_CHECK_STATE		if(state == STOPPED)						\
									return status;				    		\
								else if(state != ACQUIRED)			    	\
									return DHT11_ERROR_ACQUIRING;

class ArduDHT11
{
public:
	ArduDHT11();
	void init(int pin, int intNumber, void(*isrCallback_wrapper)());
	void isrCallback();
	int acquire();
	void acquireAndWait();
	float getTemperature();
	float getHumidity();
	bool acquiring();
	int getStatus();

private:

	// callback wrapper
	void(*isrCallback_wrapper)(void);

	// states
	enum states { RESPONSE = 0, DATA = 1, ACQUIRED = 2, STOPPED = 3, ACQUIRING = 4 };

	// variables
	volatile states state;
	volatile int status;
	volatile byte bits[5];
	volatile byte cnt;
	volatile byte idx;
	volatile int us;
	int intNumber;
	int pin;
	volatile float hum;
	volatile float temp;
};
#endif
