/*******************************************************************************
 * XLCD.cpp
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
#include "XLCD.h"

#if defined(__XHW__)

XLCD::XLCD(XLCDI& i)
	: I(i)
{
	m_inverted = false;
	m_contrast = 0;
}

// ********************************************************************************

void XLCD::Init()
{
	I.Init();
	I.Enable();
	OnOff();
	OnInit();
	OnInvert();
	OnContrast();
	OnClear();
	OnOn();
	I.Disable();
}

void XLCD::On()
{
	I.Enable();
	OnOn();
	I.Disable();
}

void XLCD::Off()
{
	I.Enable();
	OnOff();
	I.Disable();
}

void XLCD::Invert(bool inverted)
{
	if (inverted == m_inverted)
		return;
	I.Enable();
	m_inverted = inverted;
	OnInvert();
	I.Disable();
}

void XLCD::Contrast(uint8_t contrast)
{
	if (contrast == m_contrast)
		return;
	I.Enable();
	m_contrast = contrast;
	OnContrast();
	I.Disable();
}

void XLCD::Clear()
{
	I.Enable();
	OnClear();
	I.Disable();
}

#endif // __XHW__
