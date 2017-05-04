
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

/* Define pins */
// define analog input pins
#define PIN_SOIL_MOISTURE			A0
#define PIN_SOIL_TEMPERATURE		A1
#define PIN_LIGHT_INTENSITY			A2

// define DHT (external interrupt)
#define PIN_DHT						2
#define DHT_INT_NUMBER				0
#define DHT_INIT_TIME				2000

// define bluetooth (SoftwareSerial)
#define PIN_TX_BLUETOOTH			5
#define PIN_RX_BLUETOOTH			6

// define SD card
#define SD_CARD_SELECT				10

/* Define settings */
// settings hold
bool SD_CARD_AVAILIABLE;
bool DHT_SENSOR_AVAILIABLE;
bool SYSTEM_FAILING_STATE;

// serial
#define SERIAL_SPEED				9600

// water pump
#define WATER_PUMP_CYCLE_DURATION	2000

// file names
#define LOW_MOISTURE_FIELD			"00CONFIG.SET"
#define LOG_FILENAME				"ARDULOG0.LOG"

// fields
enum SETTINGS_FIELDS {
	LOW_MOISTURE_VALUE,

	SCHEDULE_TIME,
	SCHEDULE_DATE,
};

/* Status codes */
// message
enum StatusMessage {
	// system messages
	SYSTEM_STATUS,
	SYSTEM_CLOCK,
	SYSTEM_BLUETOOTH_STATUS,
	SYSTEM_DHT_STATUS,
	SYSTEM_SD_STATUS,
	SYSTEM_SD_LOG_FILE,
	SYSTEM_SD_SETTINGS_FILE,

	// action messages
	ACTION_WATER_SCHED,
	ACTION_WATER_LOW,
	ACTION_WATER_OVERRIDE,

	// sensor messages
	SENSOR_DHT_HUMIDITY,
	SENSOR_DHT_TEMPERATURE,
	SENSOR_SOIL_MOISTURE,
	SENSOR_SOIL_TEMP,
	SENSOR_LIGHT_INTENSITY,

	// motor messages
	MOTOR_START,
	MOTOR_STOP,
};

#define ERROR_SUCCESS		0x00
#define ERROR_FAILED		0x01
#define ERROR_PARTIAL		0x02
#endif 
