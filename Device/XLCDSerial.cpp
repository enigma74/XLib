/*******************************************************************************
 * XLCDSerial.cpp
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
