/*******************************************************************************
 * XLCDBus.cpp
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
#include "XLCDBus.h"

#if defined(__XHW__)

XLCDBus::XLCDBus(XLCDIType type, uint32_t freq)
	: XLCDI(type, freq)
{
	// predefined pins
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__)
	CS.Pin(A3);
	DC.Pin(A5);
	WR.Pin(A4);
	RST.Pin(A2);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)\
	|| defined(__32MX320F128H__) || defined(__32MX340F512H__)
	CS.Pin(40);
	DC.Pin(38);
	WR.Pin(39);
	RST.Pin(41);
#elif defined(__32MX795F512L__)
	CS.Pin(84);
	DC.Pin(82);
	WR.Pin(83);
	RST.Pin(85);
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	CS.Pin(3);
	DC.Pin(23);
	WR.Pin(22);
	RST.Pin(4);
#elif defined(__CC3200R1M1RGC__)
	CS.Pin(11);
	DC.Pin(15);
	WR.Pin(18);
	RST.Pin(32);
#endif
}

void XLCDBus::PulseWrite(uint32_t count)
{
//	if (count > 16)
//	{
//		uint32_t blocks = count >> 4;
//		count &= 0x0F;
//		do
//		{
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//			WR.PulseLow(m_delay);
//		} while (--blocks);
//		if (!count)
//			return;
//	}
	do
	{
		WR.PulseLow(m_delay);
	} while (--count);
}

void XLCDBus::OnInit()
{
	RD.InitOutput(HIGH);
	WR.InitOutput(HIGH);
}

void XLCDBus::OnBegin(bool write)
{
	RD = write;
	WR = !write;
}

#endif // __XHW__
