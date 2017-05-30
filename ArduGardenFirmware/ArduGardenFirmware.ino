/*
    ArduGardenFirmware.ino is part of ArduGarden.
    Copyright (C) 2017  Fahmi Noor Fiqri

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "TimedAction.h"
#include <SoftwareSerial.h>
#include "OneWire.h"
#include "ArduDHT11.h"
#include "ArduDS18B20.h"

#include "Definitions.h"

// wrappers
void dhtLib_callback();
void dataSend_callback();

// libraries
TimedAction _dataTimer(DELAY_REQUEST, dataSend_callback);
OneWire _soil_temp_wire(10);
ArduDHT11 _dhtSensor;
ArduDS18B20 _soil_temp;
SoftwareSerial _wifiSerial(PIN_WIFI_RECEIVE, PIN_WIFI_TRANSMIT);
#define _usbSerial Serial

// vars
float soilTemp, humid, moist, airTemp, light;

// ===== PROGRAM ENTRY ==============================================
void setup() {
	// begin serial communication
	usbSerialInit();
	wifiInit();

	// init sensors
	_dhtSensor.init(PIN_DHT, DHT_INT_NUMBER, dhtLib_callback);
	delay(DHT_INIT_TIME);
	_soil_temp.init(&_soil_temp_wire);
}

void loop() {
	// report from soil mositure sensor
	moist = toPercentage(analogRead(PIN_SOIL_MOISTURE));
	usbSerialSend(SENSOR_SOIL_MOISTURE, moist);

	// report from light intensity sensor
	//light = toPercentage(analogRead(PIN_LIGHT_INTENSITY));
	//usbSerialSend(SENSOR_LIGHT_INTENSITY, light);

	/* acquire data */
	_dhtSensor.acquireAndWait();
	// report celcius from DHT
	airTemp = _dhtSensor.getTemperature();
	usbSerialSend(SENSOR_DHT_TEMPERATURE, airTemp);

	// report RH from DHT
	humid = _dhtSensor.getHumidity();
	usbSerialSend(SENSOR_DHT_HUMIDITY, humid);

	// report from soil temp sensor
	soilTemp = _soil_temp.getTemperature();
	usbSerialSend(SENSOR_SOIL_TEMP, soilTemp);

	// send to server
	//_dataTimer.check();

	// delay
	delay(DELAY_CHECK);
}

