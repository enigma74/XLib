/*******************************************************************************
 * XCTE16.cpp
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
#include "XCTE16.h"

#if defined(__XCTE16__)

XCTE16::XCTE16(uint32_t freq)
	: XLCDBus16(freq)
{
	CS.Pin(27);
	DC.Pin(25);
	WR.Pin(26);
	RST.Pin(28);
}

void XCTE16::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
	REG_PIOC_OER = 0x000FF1FE;
}

void XCTE16::OnWriteBus(uint16_t data)
{
	uint32_t d = data;
	REG_PIOC_CODR = 0x000FF1FE;
	REG_PIOC_SODR = ((d & 0x0000FF00) << 4) | ((d & 0x000000FF) << 1);
}

#endif // __XCTE16__
