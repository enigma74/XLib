/*******************************************************************************
 * XIO.cpp
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

#include "XMain.h"
#include "XIO.h"

#if defined(__XHW__)

XIO::XIO(uint8_t pin)
{
	Pin(pin);
}

void XIO::Pin(uint8_t pin)
{
	m_pin = pin;
	m_output = false;
	m_pr = NULL;
	m_bm = 0;
}

void XIO::Init(uint8_t mode)
{
	if (m_pin == X_NoPin)
		return;
	m_output = (mode == OUTPUT);
	m_pr = m_output
		? portOutputRegister(digitalPinToPort(m_pin))
		: portInputRegister(digitalPinToPort(m_pin));
	m_bm = digitalPinToBitMask(m_pin);
	pinMode(m_pin, mode);
}

#endif // __XHW__
