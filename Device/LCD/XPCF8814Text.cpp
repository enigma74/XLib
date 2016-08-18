/*******************************************************************************
 * XPCF8814Text.cpp
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
#include "XPCF8814Text.h"

#include "../../Graph/Renderers/XTextRenderer.h"

#if defined(__XHW__)

XPCF8814Text::XPCF8814Text(XLCDSerial& i)
	: XLCD(i), Rect(XSize(96, 8))
{
	m_contrast = 0x45;
}

void XPCF8814Text::OnInit()
{
	// Power Control (0x28: Charge Pump Off, 0x2C: Charge Pump On)
	I.Command(0x2C);
	// Charge Pump Control
	I.Command(0x3D);
	I.Command(0x00); // (0x00: X2, 0x01: X3, 0x02: X4, 0x03: X5)
	delay(120);
	// Y Mirroring (0xC8: On, 0xC0: Off)
	I.Command(0xC0);
	// RAM Address Mode (0xAA: Horizontal, 0xAB: Vertical)
	I.Command(0xAA);
}

void XPCF8814Text::OnOn()
{
	// Display On
	I.Command(0xAF);
	// All Pixel On (0xA5: Enable, 0xA4: Disable)
	I.Command(0xA4);
}

void XPCF8814Text::OnOff()
{
	// Display Off
	I.Command(0xAE);
	// All Pixel On (0xA5: Enable, 0xA4: Disable)
	I.Command(0xA5);
}

void XPCF8814Text::OnInvert()
{
	// Invert (0xA7: Enable, 0xA6: Disable)
	if (m_inverted)
		I.Command(0xA7);
	else
		I.Command(0xA6);
}

void XPCF8814Text::OnContrast()
{
	// Set Vop
	I.Command(0x20 | ((m_contrast >> 5) & 0x03));
	I.Command(0x80 | (m_contrast & 0x1F));
}

void XPCF8814Text::OnLocation(XPoint p)
{
	// Vertical addressing
	I.Command(0xB0 | (p.y & 0x0F));
	// Horizontal addressing
	I.Command(p.x & 0x0F);
	I.Command(0x10 | ((p.x >> 4) & 0x07));
}

void XPCF8814Text::OnClear()
{
	OnLocation(XPoint());
	uint32_t count = 9 * 96;
	do
	{
		I.WriteByte(0x00);
	} while (--count);
}

void XPCF8814Text::Text(XRect rect, const XText& text, bool invert)
{
	rect = Rect.Fix(rect);
	if (rect.IsEmpty() || text.IsEmpty())
		return;
	I.Enable();
	// write data and function
	uint8_t buff[96];
	uint8_t back = invert ? 0xFF : 0x00;
	XPoint a = rect.Location;
	XPoint b = rect.Ending();
	int8_t y = -1;
	auto _Flush = [this, &buff, &back, &a, &b, &y](int8_t _y)
	{
		while (y < _y)
		{
			if (y >= 0)
				OnLocation(XPoint(a.x, y));
			for (int x = a.x; x <= b.x; x++)
			{
				if (y >= 0)
					I.WriteByte(buff[x]);
				buff[x] = back;
			}
			if (y < 0)
				y = a.y;
			else
				y++;
		}
	};
	// text rendering
	rect.Location.y <<= 3;
	rect.Size.Height <<= 3;
	XTextRenderer tr(rect, &text, 8);
	while (tr.Next())
	{
		if (tr.Alpha() != 0xFF)
			continue;
		XPoint l = tr.Location();
		_Flush(l.y >> 3);
		uint8_t bm = 0x01 << (l.y % 8);
		if (invert)
			buff[l.x] &= ~bm;
		else
			buff[l.x] |= bm;
	}
	_Flush(b.y + 1);
	I.Disable();
}

#endif // __XHW__
