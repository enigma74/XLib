/*******************************************************************************
 * XElecHouse16.cpp
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
#include "XElecHouse16.h"

#if defined(__XElecHouse16__)

XElecHouse16::XElecHouse16(uint32_t freq)
	: XLCDBus16(freq)
{
	CS.Pin(31);
	DC.Pin(22);
	RD.Pin(24);
	WR.Pin(23);
	RST.Pin(33);
}

void XElecHouse16::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
	REG_PIOC_OER = 0x000FF3FC;
}

void XElecHouse16::OnWriteBus(uint16_t data)
{
	uint32_t d = data;
	REG_PIOC_CODR = 0x000FF3FC;
	REG_PIOC_SODR = ((d & 0x0000FF00) << 4) | ((d & 0x000000FF) << 2);
}

#endif // __XElecHouse16__
