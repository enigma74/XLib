/*******************************************************************************
 * XLCDBus.cpp
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
