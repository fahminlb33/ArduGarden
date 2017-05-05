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

bool SETTINGS_USE_DEFAULTS = false;

void resetSystemVariables() {
	SD_CARD_AVAILIABLE = false;
	DHT_SENSOR_AVAILIABLE = false;
	SYSTEM_FAILING_STATE = false;
}

void initializeSettings() {
	// vars
	bool hasErrors = false;

	// check file paths
	if (!SD.exists(LOW_MOISTURE_FIELD)) hasErrors = true;
	//...

	// prep
	SETTINGS_USE_DEFAULTS = hasErrors;
}

// DOC:  read saved settings, or use default one
int readSetting(SETTINGS_FIELDS field) {
	// load
	switch (field)
	{
	case LOW_MOISTURE_VALUE:
		if (SETTINGS_USE_DEFAULTS)
		{
			return 700;
		}
		else
		{
			return readSDFile(LOW_MOISTURE_FIELD);
		}
		break;

	default:
		break;
	}
}

// DOC: format string
String formatData(StatusMessage message, float parameter) {
	return String(message) + String(":") + String(parameter);
}

