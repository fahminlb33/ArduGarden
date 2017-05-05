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