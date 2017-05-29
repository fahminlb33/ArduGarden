/*
    TimedAction.h is part of ArduGarden.
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

#ifndef _TIMEDACTION_h
#define _TIMEDACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class TimedAction {

public:
	TimedAction(unsigned long interval, void(*function)());

	void setRunMode(bool loop);
	void reset();
	void check();
	void setPrevious(unsigned long prev);

private:
	bool active;
	bool loopMode;
	unsigned long previous;
	unsigned long interval;
	void(*execute)();

};

#endif

