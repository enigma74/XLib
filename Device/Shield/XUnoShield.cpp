/*******************************************************************************
 * XUnoShield.cpp
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
#include "XUnoShield.h"

#if defined(__XUnoShield__)

XUnoShield::XUnoShield(uint32_t freq)
	: XLCDBus8(XLCDIType::Parallel8, freq)
{
	CS.Pin(A3);
	DC.Pin(A5);
	WR.Pin(A4);
	RST.Pin(A2);
}

void XUnoShield::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	DDRH = 0x18;
	DDRG = 0x20;
	DDRE = 0x3B;
#endif
}

void XUnoShield::OnWriteBus(uint8_t data)
{
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	X_ClearFlag(PORTG, 0x20);
	X_SetFlag(PORTG, (data & 0x10) << 1);
	X_ClearFlag(PORTH, 0x18);
	X_SetFlag(PORTH,  (data & 0xC0) >> 3);
	X_ClearFlag(PORTE, 0x3B);
	X_SetFlag(PORTE,  (data & 0x03) | ((data & 0x0C) << 2) | ((data & 0x20) >> 2));
#endif
}

#endif // __XUnoShield__
