/*
  wiring_pulse.c - pulseIn() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/

#include "wiring_private.h"
#include "pins_arduino.h"

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
	rt_uint32_t begin_tick;
	rt_uint32_t current_tick;

	while (digitalRead(pin) == state) ;

	begin_tick = current_tick = micros();
	timeout = begin_tick + timeout;
	while (current_tick < timeout)
	{
		if (digitalRead(pin) != state)
		{
			return current_tick - begin_tick;
			break;
		}
		current_tick = micros();
	}

	return 0;
}
