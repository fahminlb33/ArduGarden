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

int initUsbSerial() {
	// begin serial
	Serial.begin(SERIAL_SPEED);

	// wait for serial (uneeded for external Serial IC)
	/*while (!Serial) {
	;
	}*/

	// return success
	return ERROR_SUCCESS;
}

int initDHT() {
	// prepare DHT
	_dhtSensor.init(PIN_DHT, DHT_INT_NUMBER, dhtLib_wrapper);
	delay(DHT_INIT_TIME);

	// test get data
	_dhtSensor.acquireAndWait();

	// get status
	if (_dhtSensor.getStatus() == DHT11_OK)
	{
		return ERROR_SUCCESS;
	}
	else
	{
		return ERROR_FAILED;
	}
}

int initBluetooth() {
	// begin bluetooth serial
	_bluetoothSerial.begin(9600);

	// always OK
	return ERROR_SUCCESS;
}

int initSD() {
	// open sd card
	if (SD.begin(SD_CARD_SELECT))
	{
		return ERROR_SUCCESS;
	}
	else
	{
		return ERROR_FAILED;
	}
}

/*
Provides sensors value collecting
*/

void readSensors() {
	// report status from sensors
	int currentValue = 0;

	// acquire data
	_dhtSensor.acquireAndWait();

	// report from DHT
	currentValue = _dhtSensor.getStatus();
	omniWrite(SYSTEM_DHT_STATUS, currentValue);

	// report celcius from DHT
	currentValue = _dhtSensor.getTemperature();
	omniWrite(SENSOR_DHT_TEMPERATURE, currentValue);

	// report RH from DHT
	currentValue = _dhtSensor.getHumidity();
	omniWrite(SENSOR_DHT_HUMIDITY, currentValue);

	// report from soil mositure sensor
	currentValue = analogRead(PIN_SOIL_MOISTURE);
	omniWrite(SENSOR_SOIL_MOISTURE, currentValue);

	// report from soil temp sensor
	currentValue = analogRead(PIN_SOIL_TEMPERATURE);
	omniWrite(SENSOR_SOIL_TEMP, currentValue);

	// report from light intensity sensor
	currentValue = analogRead(PIN_LIGHT_INTENSITY);
	omniWrite(SENSOR_LIGHT_INTENSITY, currentValue);
}

void checkSoilMoisture() {
	int currentValue = analogRead(PIN_SOIL_MOISTURE);
	if (currentValue <= readSetting(LOW_MOISTURE_VALUE))
	{
		// send info
		omniWrite(ACTION_WATER_LOW, ERROR_SUCCESS);

		// pump one cycle
		waterPumpOneCycle();
	}
}

void checkScheduledWatering() {
	// TODO: Implement this
}

void dhtLib_wrapper() {
	_dhtSensor.isrCallback();
}
