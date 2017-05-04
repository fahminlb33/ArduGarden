/*
System configuration helper
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

