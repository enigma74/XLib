/*******************************************************************************
 * XPCF8814.cpp
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
#include "XPCF8814.h"

#include "../../Graph/Renderers/XTextRenderer.h"

#if defined(__XHW__)

XPCF8814::XPCF8814(XLCDSerial& i)
	: XGLCD(XSize(96, 65), i)
{
	m_contrast = 0x45;
}

void XPCF8814::OnInit()
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

void XPCF8814::OnOn()
{
	// Display On
	I.Command(0xAF);
	// All Pixel On (0xA5: Enable, 0xA4: Disable)
	I.Command(0xA4);
}

void XPCF8814::OnOff()
{
	// Display Off
	I.Command(0xAE);
	// All Pixel On (0xA5: Enable, 0xA4: Disable)
	I.Command(0xA5);
}

//bool XPCF8814::OnRotate()
//{
//	// Memory Access Control
//	I.Command(0x36);
//	uint8_t b = 0x08; // BGR
//	uint8_t flags = XGLCD::RotateFlags(X_LCDSwap, m_rotation);
//	if (X_GetFlag(flags, X_LCDHFlip))
//		b |= 0x40; // Column Address Order
//	if (X_GetFlag(flags, X_LCDVFlip))
//		b |= 0x80; // Row Address Order
//	if (X_GetFlag(flags, X_LCDSwap))
//		b |= 0x20; // Swap X/Y
//	I.WriteByte(b);
//	return true;
//}

void XPCF8814::OnInvert()
{
	// Invert (0xA7: Enable, 0xA6: Disable)
	if (m_inverted)
		I.Command(0xA7);
	else
		I.Command(0xA6);
}

void XPCF8814::OnContrast()
{
	// Set Vop
	I.Command(0x20 | ((m_contrast >> 5) & 0x03));
	I.Command(0x80 | (m_contrast & 0x1F));
}

void XPCF8814::OnLocation(XPoint l)
{
	// Vertical addressing
	I.Command(0xB0 | (l.y & 0x0F));
	// Horizontal addressing
	I.Command(l.x & 0x0F);
	I.Command(0x10 | ((l.x >> 4) & 0x07));
}

void XPCF8814::OnClear()
{
	XPoint l;
	OnLocation(l);
	for (l.y = 0; l.y < 9; l.y++)
		for (l.x = 0; l.x < 96; l.x++)
		{
			m_buff[l.x][l.y] = 0x00;
			I.WriteByte(0x00);
		}
}

void XPCF8814::OnBeginFunction()
{
	XDisplay::OnBeginFunction();
	//I.Enable();
}

void XPCF8814::OnEndFunction()
{
	//I.Disable();
	XDisplay::OnEndFunction();
}

void XPCF8814::OnEndSequence()
{
	// write changed buffer to display
	I.Enable();
	XPoint l;
	bool loc = true;
	for (l.y = 0; l.y < 9; l.y++)
	{
		if (!m_buff[96][l.y])
		{
			loc = true;
			continue;
		}
		for (l.x = 0; l.x < 96; l.x++)
		{
			if (!(m_buff[l.x][8] & 0x80))
			{
				loc = true;
				continue;
			}
			if (loc)
			{
				OnLocation(l);
				loc = false;
			}
			I.WriteByte(m_buff[l.x][l.y]);
		}
	}
	I.Disable();
}

void XPCF8814::OnFill(const XRect& rect, const XColor& color)
{
	// rendering to buffer
	XPoint a = rect.Location;
	XPoint b = rect.Ending();
	XColor c = color.To(XColorMode::Mono);
	bool black = (c.r + c.g + c.b) == 0;
	XPoint l;
	for (l.y = a.y; l.y <= b.y; l.y++)
	{
		int y = l.y >> 3;
		uint8_t bm = 0x01 << (l.y % 8);
		m_buff[96][y] = 1;
		for (l.x = a.x; l.x <= b.x; l.x++)
		{
			if (black)
				m_buff[l.x][y] |= bm;
			else
				m_buff[l.x][y] &= ~bm;
			m_buff[l.x][8] |= 0x80;
		}
	}
}

#endif // __XHW__
