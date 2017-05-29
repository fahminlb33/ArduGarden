/*
    TimedAction.cpp is part of ArduGarden.
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

#include "TimedAction.h"

TimedAction::TimedAction(unsigned long intervl, void(*function)()) {
	active = true;
	previous = 0;
	interval = intervl;
	execute = function;
	loopMode = true;
}

void TimedAction::setRunMode(bool loop) {
	loopMode = loop;
}

void TimedAction::reset() {
	previous = millis();
}

void TimedAction::setPrevious(unsigned long prev) {
	previous = prev;
}

void TimedAction::check() {
	if (active && (millis() - previous >= interval)) {
		if (!loopMode) active = false;
		previous = millis();
		execute();
	}
}