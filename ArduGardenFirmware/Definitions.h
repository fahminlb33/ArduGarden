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

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

/* Define pins */
// define analog input pins
#define PIN_SOIL_TEMPERATURE		10
#define PIN_SOIL_MOISTURE			A0
#define PIN_LIGHT_INTENSITY			A1
// define DHT (external interrupt)
#define PIN_DHT						2
#define DHT_INT_NUMBER				digitalPinToInterrupt(PIN_DHT)
#define DHT_INIT_TIME				2000
// define wifi (SoftwareSerial)
#define PIN_WIFI_TRANSMIT			6
#define PIN_WIFI_RECEIVE			7

/* Define settings */
// delays
#define DELAY_REQUEST				16000
#define DELAY_CHECK					1000
// serial
#define SERIAL_SPEED				9600
#define SERIAL_DATA_DELIMITER		"|"
// IoT api
#define THINGSPEAK_API_KEY			"M6S4VTLNJ6M2XE8K"
#define THINGSPEAK_ENDPOINT			"184.106.153.149"

/* Status codes */
enum StatusMessage {
	SENSOR_DHT_HUMIDITY,
	SENSOR_DHT_TEMPERATURE,
	SENSOR_SOIL_MOISTURE,
	SENSOR_SOIL_TEMP,
	SENSOR_LIGHT_INTENSITY,
};

#endif 
