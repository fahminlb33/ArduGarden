/*
    Serial.ino is part of ArduGarden.
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

void usbSerialInit() {
	_usbSerial.begin(SERIAL_SPEED);
}

void usbSerialSend(uint8_t field, float value) {
	String data = "";
	
	switch (field)
	{
	case SENSOR_DHT_HUMIDITY:
		data.concat("HUMIDITY");
		break;
	case SENSOR_DHT_TEMPERATURE:
		data.concat("AIRTEMP");
		break;
	case SENSOR_SOIL_MOISTURE:
		data.concat("SOILMOIST");
		break;
	case SENSOR_SOIL_TEMP:
		data.concat("SOILTEMP");
		break;
	case SENSOR_LIGHT_INTENSITY:
		data.concat("LIGHTLUX");
		break;
	default:
		data.concat("UNKNOWN");
		break;
	}
	data.concat(SERIAL_DATA_DELIMITER);
	data.concat(value);

	_usbSerial.println(data);
}