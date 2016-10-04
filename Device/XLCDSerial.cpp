/*******************************************************************************
 * XLCDSerial.cpp
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
#include "XLCDSerial.h"

#if defined(__XHW__)

XLCDSerial::XLCDSerial(uint32_t freq)
	: XLCDI(XLCDIType::Serial, freq)
{
}

void XLCDSerial::OnInit()
{
	SDA.InitOutput(HIGH);
	SCL.InitOutput(HIGH);
}

void XLCDSerial::OnWriteByte(uint8_t data, bool cmd)
{
	if (!DC.IsInit())
	{
		SDA = !cmd;
		SCL.PulseLow(m_delay);
	}
	for (int b = 0; b < 8; b++)
	{
		SDA = data & 0x80;
		SCL.PulseLow(m_delay);
		data <<= 1;
	}
//	SDA = data & 0x80;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x40;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x20;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x10;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x08;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x04;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x02;
//	SCL.PulseLow(m_delay);
//	SDA = data & 0x01;
//	SCL.PulseLow(m_delay);
}

void XLCDSerial::OnWriteColor(XColor color, uint32_t count)
{
	switch (color.Mode())
	{
		case XColorMode::RGB111:
		{
			// 1 byte per 2px (LSB 6bits)
			uint8_t b = color.Encode();
			b |= b << 3;
			count += (count % 2);
			do
			{
				OnWriteByte(b);
			} while (count -= 2);
			break;
		}
		case XColorMode::RGB565:
		{
			// 2 bytes per 1px (MSB and LSB)
			uint16_t rgb = color.Encode();
			uint8_t ch = XHiByte(rgb);
			uint8_t cl = XLoByte(rgb);
			do
			{
				OnWriteByte(ch);
				OnWriteByte(cl);
			} while (--count);
			break;
		}
		case XColorMode::RGB666:
		{
			// 3 bytes per 1px (MSB 6bits component per byte)
			color.r <<= 2;
			color.g <<= 2;
			color.b <<= 2;
			do
			{
				OnWriteByte(color.r);
				OnWriteByte(color.g);
				OnWriteByte(color.b);
			} while (--count);
			break;
		}
		default:
			break;
	}
}

#endif // __XHW__
