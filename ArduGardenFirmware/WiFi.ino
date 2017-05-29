/*
    WiFi.ino is part of ArduGarden.
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

void wifiInit() {
	_wifiSerial.begin(SERIAL_SPEED);
	_wifiSerial.println("AT+RST");
}

bool wifiBeginTcp() {
	// data
	String cmd = "AT+CIPSTART=";
	cmd.concat("\"TCP\","); // connection type
	cmd.concat("\"");
	cmd.concat(THINGSPEAK_ENDPOINT);
	cmd.concat("\",");
	cmd.concat("80"); // port

	_wifiSerial.println(cmd);
	return !_wifiSerial.find("Error");
}

void wifiCloseTcp() {
	_wifiSerial.println("AT+CIPCLOSE");
}

void wifiHttpSend() {
	// data payload
	String payload = "GET /update?api_key=";
	payload.concat(THINGSPEAK_API_KEY);
	payload.concat("&field1");
	payload.concat("=");
	payload.concat(soilTemp);
	payload.concat("&field2");
	payload.concat("=");
	payload.concat(humid);
	payload.concat("&field3");
	payload.concat("=");
	payload.concat(moist);
	payload.concat("&field4");
	payload.concat("=");
	payload.concat(airTemp);
	payload.concat("&field5");
	payload.concat("=");
	payload.concat(light);
	payload.concat("\r\n\r\n");

	// command
	String cmd = "AT+CIPSEND=";
	cmd.concat(payload.length());
	_wifiSerial.println(cmd);

	// send http
	if (_wifiSerial.find(">")) {
		_wifiSerial.print(payload);
	}
}