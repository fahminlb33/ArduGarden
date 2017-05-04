/*
Name:		ArduGardenCore.ino
Created:	2/12/2017 6:53:39 PM
Author:	Fahmi
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