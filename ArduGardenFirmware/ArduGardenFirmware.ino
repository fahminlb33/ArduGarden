/*
    ArduGardenFirmware.ino  is part of ArduGarden.
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

#include <SD.h>
#include <SoftwareSerial.h>
#include "OneWire.h"
#include "ArduDHT11.h"
#include "ArduDS3231.h"
#include "ArduDS18B20.h"

#include "Definitions.h"

// libraries
OneWire _soil_temp_wire(10);
ArduDHT11 _dhtSensor;
ArduDS3231 _rtc;
ArduDS18B20 _soil_temp;
SoftwareSerial _bluetoothSerial(PIN_RX_BLUETOOTH, PIN_TX_BLUETOOTH);
#define _usbSerial Serial

// wrappers
void dhtLib_wrapper();

// ===== PROGRAM ENTRY ==============================================
void setup() {
	// initialize modules
	initializeSystem();

	// read settings
	initializeSettings();
}

void loop() {
	// get command
	String cmd = getSerialCommand();

	// step 1 - read sensors
	readSensors();

	// step 2 - check for watering schedule
	// --- check soil moisture
	checkSoilMoisture();
	// --- check scheduled time
	checkScheduledWatering();

	// step 3 - parse command

}

void initializeSystem() {
	// initialize system
	int errorCount = 0;
	int returnCode = ERROR_SUCCESS;

	// reset
	resetSystemVariables();

	// begin serial communication
	initUsbSerial();

	// init bluetooth
	returnCode = initBluetooth();
	omniWrite(SYSTEM_BLUETOOTH_STATUS, returnCode);
	if (returnCode != ERROR_SUCCESS) errorCount++;

	// init dht
	returnCode = initDHT();
	omniWrite(SYSTEM_DHT_STATUS, returnCode);
	if (returnCode != ERROR_SUCCESS) {
		errorCount++;
		DHT_SENSOR_AVAILIABLE = false;
	}
	else
	{
		DHT_SENSOR_AVAILIABLE = true;
	}

	// init soil temp
	_soil_temp.init(&_soil_temp_wire);

	// init SD
	returnCode = initSD();
	omniWrite(SYSTEM_SD_STATUS, returnCode);
	if (returnCode != ERROR_SUCCESS) {
		errorCount++;
		SD_CARD_AVAILIABLE = false;
	}
	else
	{
		SD_CARD_AVAILIABLE = true;
	}

	// send system status
	if (errorCount == 0) {
		omniWrite(SYSTEM_STATUS, ERROR_SUCCESS);
		SYSTEM_FAILING_STATE = false;
	}
	else if (errorCount == 3)
	{
		omniWrite(SYSTEM_STATUS, ERROR_FAILED);
		SYSTEM_FAILING_STATE = true;
	}
	else
	{
		omniWrite(SYSTEM_STATUS, ERROR_PARTIAL);
		SYSTEM_FAILING_STATE = false;
	}
}