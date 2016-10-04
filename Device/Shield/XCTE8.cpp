/*******************************************************************************
 * XCTE8.cpp
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
#include "XCTE8.h"

#if defined(__XCTE8__)

XCTE8::XCTE8(uint32_t freq)
	: XLCDBus8(freq)
{
	CS.Pin(27);
	DC.Pin(25);
	WR.Pin(26);
	RST.Pin(28);
}

void XCTE8::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
	REG_PIOC_OER = 0x000FF000;
}

void XCTE8::OnWriteBus(uint8_t data)
{
	REG_PIOC_CODR = 0x000FF000;
	REG_PIOC_SODR = (data << 12) & 0xFF000;
}

#endif // __XCTE8__
