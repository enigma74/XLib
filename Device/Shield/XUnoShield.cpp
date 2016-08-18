/*******************************************************************************
 * XUnoShield.cpp
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
