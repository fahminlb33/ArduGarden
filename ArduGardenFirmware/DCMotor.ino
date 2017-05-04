

void waterPumpOneCycle() {
	// start pump
	waterPumpStart();

	// wait
	delay(WATER_PUMP_CYCLE_DURATION);

	// stop pump
	waterPumpStop();
}

void waterPumpStart() {
	omniWrite(MOTOR_START, ERROR_SUCCESS);
}

void waterPumpStop() {
	omniWrite(MOTOR_STOP, ERROR_SUCCESS);
}