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

String formatData(StatusMessage message, float parameter) {
	String formatted = "";

	// message
	formatted.concat(message);
	formatted.concat(SERIAL_PACK_DELIMITER);
	formatted.concat(parameter);

	return formatted;
}
String formatDateTime(DateTime time) {
	String formatted = "";

	// day
	formatted.concat(time.date);
	// mon
	formatted.concat(SERIAL_DATA_DELIMITER);
	formatted.concat(time.date);
	// year
	formatted.concat(SERIAL_DATA_DELIMITER);
	formatted.concat(time.year);
	// hour
	formatted.concat(SERIAL_DATA_DELIMITER);
	formatted.concat(time.hour);
	// min
	formatted.concat(SERIAL_DATA_DELIMITER);
	formatted.concat(time.min);
	// sec
	formatted.concat(SERIAL_DATA_DELIMITER);
	formatted.concat(time.sec);

	return formatted;
}
