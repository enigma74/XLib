/*******************************************************************************
 * XAquaLED.cpp
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * This file is part of XLib.
 *
 * XLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

#include "XDevice.h"
#include "XAquaLED.h"

#if defined(__XAquaLED__)

XAquaLED::XAquaLED(uint32_t freq)
	: XLCDBus16(freq)
{
}

void XAquaLED::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
	TRISA = 0;
	TRISE = 0;
}

void XAquaLED::OnWriteBus(uint16_t data)
{
	LATACLR = 0xFF;
	LATASET = data & 0xFF;
	LATECLR = 0xFF;
	LATESET = (data >> 8);
}

#endif // __XCTE__
