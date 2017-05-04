/*
I/O process methods
*/

//DOC:  log to both 
void omniWrite(StatusMessage message, float parameter, bool writeSD) {
	// write to USB serial
	writeToUsbSerial(message, parameter);

	// write to bluetooth
	writeToBluetoothSerial(message, parameter);

	// write to SD
	if (SD_CARD_AVAILIABLE && writeSD)
	{
		writeToSD(message, parameter);
	}
}

//DOC: log to sd card
void writeToSD(StatusMessage message, float parameter) {
	// check for SD card
	if (!SD_CARD_AVAILIABLE) return;

	// opens log file
	File logFile = SD.open(LOG_FILENAME, FILE_WRITE);

	// check file
	if (!logFile) {
		// log error
		omniWrite(SYSTEM_SD_LOG_FILE, ERROR_FAILED, false);
	}
	else
	{
		// get current time
		// TODO:  implement RTC data
		String currentTime = "";

		// write to file
		logFile.println(currentTime + formatData(message, parameter));

		// closes the file
		logFile.close();
	}
}

// DOC:  send value using serial
void writeToUsbSerial(StatusMessage message, float parameter) {
	// write to serial
	_usbSerial.println(formatData(message, parameter));
}

// DOC:  write to bluetooth serial
void writeToBluetoothSerial(StatusMessage message, float parameter) {
	// write to serial
	_bluetoothSerial.println(formatData(message, parameter));
}

int readSDFile(String fileName) {
	// open file
	File file = SD.open(LOW_MOISTURE_FIELD);

	// check file 
	if (!file) {
		// log
		omniWrite(SYSTEM_SD_SETTINGS_FILE, ERROR_FAILED, false);
		return -1;
	}
	else
	{
		// read data
		int data = file.parseInt();

		// close file
		file.close();

		// return
		return data;
	}
}

// DOC:  get command from serial
String getSerialCommand() {
	if (!Serial.available()) return "";

	// read string
	

	return "";
}
